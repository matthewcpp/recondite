#include "ui/ruiOverlay.hpp"

#include "ui/ruiWidget.hpp"
#include "ui/ruiLayout.hpp"
#include "stream/rOStringStream.hpp"
#include "ui/ruiMenuManager.hpp"

struct ruiOverlay::Impl{
	std::vector<ruiWidget*> widgets;

	ruiWidget* activeWidget;
	ruiWidget* modalWidget;
	ruiLayout* layout;
	rViewport* viewport;
	ruiController* controller;

	ruiStyleManager styleManager;
	ruiMenuManager menuManager;

	Impl(rEngine* _engine, rViewport* _viewport)
		:activeWidget(nullptr), viewport(_viewport), menuManager(_engine), controller(nullptr) {}
};

ruiOverlay::ruiOverlay(rEngine* engine, rViewport* viewport){
	_impl = new Impl(engine, viewport);

	_impl->activeWidget = NULL;
	_impl->layout = NULL;
	_impl->viewport = viewport;
}

ruiOverlay::~ruiOverlay(){
	delete _impl;
}

void ruiOverlay::AddWidget(ruiWidget* widget){
	_impl->widgets.push_back(widget);
}

ruiWidget* ruiOverlay::GetWidget(const rString& id){
	for (size_t i = 0; i < _impl->widgets.size(); i++){
		if (_impl->widgets[i]->Id() == id)
			return _impl->widgets[i];
	}

	return NULL;
}

void ruiOverlay::Update(){
	for (size_t i = 0; i < _impl->widgets.size(); i++)
		_impl->widgets[i]->Update();

	UpdateLayout();
}

void ruiOverlay::UpdateLayout(bool force){
	if (_impl->layout){
		rRect layoutRect = _impl->viewport->GetScreenRect();
			_impl->layout->Layout(layoutRect);
        }
}

void ruiOverlay::Draw(){
	for (size_t i = 0; i < _impl->widgets.size(); i++)
		_impl->widgets[i]->Draw();

	_impl->menuManager.Draw();
}

void ruiOverlay::Clear(){
	for (size_t i = 0; i < _impl->widgets.size(); i++)
		delete _impl->widgets[i];
	
	_impl->widgets.clear();
}

ruiWidget* ruiOverlay::SelectWidget(const rPoint& position){
	rRect boundingBox;

	for (size_t i = 0; i < _impl->widgets.size(); i++){
		boundingBox = _impl->widgets[i]->BoundingBox();

		if (boundingBox.ContainsPoint(position)){
			return _impl->widgets[i];
		}
	}

	return NULL;
}

ruiLayout* ruiOverlay::Layout() const{
	return _impl->layout;
}

void ruiOverlay::SetLayout(ruiLayout* layout){
	if (_impl->layout)
		delete _impl->layout;
	
	_impl->layout = layout;
}

rString ruiOverlay::GetDefaultId () const{
	rOStringStream str("item");
	str << _impl->widgets.size();

	return str.Str();
}

ruiStyleManager* ruiOverlay::Styles(){
	return &_impl->styleManager;
}

bool ruiOverlay::ShowContextMenu(ruiMenu* menu, ruiStyle* style, const rPoint& position, rEventHandler* handler){
	return _impl->menuManager.ShowContextMenu(menu, style, position, handler);
}

void ruiOverlay::CancelContextMenu(){
	_impl->menuManager.CancelContextMenu();
}

ruiController* ruiOverlay::GetController(){
	return _impl->controller;
}

void ruiOverlay::SetController(ruiController* controller){
	_impl->controller = controller;
}

void ruiOverlay::ProcessMouseDownEvent(ruiMouseEvent& event){
	if (_impl->menuManager.OnPointerDown(event.Position())) return;

	if (_impl->activeWidget){
		_impl->activeWidget->Trigger(ruiEVT_MOUSE_DOWN, event);
		_impl->activeWidget->UiState("active");
	}
}

void ruiOverlay::ProcessMouseMotionEvent(ruiMouseEvent& event){
	rPoint position = event.Position();
	if (_impl->activeWidget){
		rRect boundingBox = _impl->activeWidget->BoundingBox();

		if (boundingBox.ContainsPoint(position)){
			_impl->activeWidget->Trigger(ruiEVT_MOUSE_MOTION, event);
		}
		else if (_impl->activeWidget->UiState() == "hover"){
			_impl->activeWidget->Trigger(ruiEVT_MOUSE_LEAVE, event);
			_impl->activeWidget->UiState("");
			_impl->activeWidget = nullptr;
		}
	}
	else {
		ruiWidget* selectedWidget = SelectWidget(position);

		if (selectedWidget){
			selectedWidget->Trigger(ruiEVT_MOUSE_ENTER, event);
			selectedWidget->UiState("hover");
			_impl->activeWidget = selectedWidget;
		}
	}
}

void ruiOverlay::ProcessMouseUpEvent(ruiMouseEvent& event){
	if (_impl->activeWidget){
		rRect boundingBox = _impl->activeWidget->BoundingBox();
		_impl->activeWidget->Trigger(ruiEVT_MOUSE_UP, event);

		if (boundingBox.ContainsPoint(event.Position())){
			_impl->activeWidget->UiState("hover");
		}

		else{
			_impl->activeWidget->UiState("");
			_impl->activeWidget = nullptr;
		}
	}
}

void ruiOverlay::ProcessMouseWheelEvent(ruiMouseEvent& event){
	if (_impl->activeWidget){
		_impl->activeWidget->Trigger(ruiEVT_MOUSE_WHEEL, event);
	}
}