#include "ui/ruiDocument.hpp"

#include <map>

#include "ui/ruiWidget.hpp"
#include "ui/ruiLayout.hpp"
#include "stream/rOStringStream.hpp"
#include "ui/ruiMenuManager.hpp"

struct ruiDocument::Impl{
	std::vector<ruiWidget*> widgets;
	std::map<uint32_t, UpdateFunc> everyUpdateFuncs;
	std::map<uint32_t, UpdateFunc> nextUpdateFuncs;
	uint32_t updateFuncHandle;

	ruiWidget* activeWidget;
	ruiWidget* modalWidget;
	ruiLayout* layout;
	rViewport* viewport;
	ruiController* controller;

	ruiStyleManager styleManager;
	ruiMenuManager menuManager;

	Impl(rEngine* _engine, rViewport* _viewport)
		:activeWidget(nullptr), viewport(_viewport), menuManager(_engine), controller(nullptr), updateFuncHandle(1){}
};

ruiDocument::ruiDocument(rEngine* engine, rViewport* viewport){
	_impl = new Impl(engine, viewport);

	_impl->activeWidget = NULL;
	_impl->layout = NULL;
	_impl->viewport = viewport;
}

ruiDocument::~ruiDocument(){
	delete _impl;
}

void ruiDocument::AddWidget(ruiWidget* widget){
	_impl->widgets.push_back(widget);
}

ruiWidget* ruiDocument::GetWidget(const rString& id){
	for (size_t i = 0; i < _impl->widgets.size(); i++){
		if (_impl->widgets[i]->Id() == id)
			return _impl->widgets[i];
	}

	return NULL;
}

void ruiDocument::Update(){
	for (auto& item : _impl->everyUpdateFuncs){
		item.second();
	}

	for (auto& item : _impl->nextUpdateFuncs){
		item.second();
	}

	_impl->nextUpdateFuncs.clear();

	for (size_t i = 0; i < _impl->widgets.size(); i++)
		_impl->widgets[i]->Update();

	UpdateLayout();
}

void ruiDocument::UpdateLayout(bool force){
	if (_impl->layout){
		rRect layoutRect = _impl->viewport->GetScreenRect();
			_impl->layout->Layout(layoutRect);
        }
}

void ruiDocument::Draw(){
	for (size_t i = 0; i < _impl->widgets.size(); i++)
		_impl->widgets[i]->Draw();

	_impl->menuManager.Draw();
}

void ruiDocument::Clear(){
	for (size_t i = 0; i < _impl->widgets.size(); i++)
		delete _impl->widgets[i];
	
	_impl->widgets.clear();
}

ruiWidget* ruiDocument::SelectWidget(const rPoint& position){
	rRect boundingBox;

	for (size_t i = 0; i < _impl->widgets.size(); i++){
		boundingBox = _impl->widgets[i]->BoundingBox();

		if (boundingBox.ContainsPoint(position)){
			return _impl->widgets[i];
		}
	}

	return NULL;
}

ruiLayout* ruiDocument::Layout() const{
	return _impl->layout;
}

void ruiDocument::SetLayout(ruiLayout* layout){
	if (_impl->layout)
		delete _impl->layout;
	
	_impl->layout = layout;
}

rString ruiDocument::GetDefaultId () const{
	rOStringStream str("item");
	str << _impl->widgets.size();

	return str.Str();
}

ruiStyleManager* ruiDocument::Styles(){
	return &_impl->styleManager;
}

bool ruiDocument::ShowContextMenu(ruiMenu* menu, ruiStyle* style, const rPoint& position, rEventHandler* handler){
	return _impl->menuManager.ShowContextMenu(menu, style, position, handler);
}

void ruiDocument::CancelContextMenu(){
	_impl->menuManager.CancelContextMenu();
}

ruiController* ruiDocument::GetController(){
	return _impl->controller;
}

void ruiDocument::SetController(ruiController* controller){
	_impl->controller = controller;
}

void ruiDocument::ProcessMouseDownEvent(ruiMouseEvent& event){
	if (_impl->menuManager.OnPointerDown(event.Position())) return;

	if (_impl->activeWidget){
		_impl->activeWidget->Trigger(ruiEVT_MOUSE_DOWN, event);
		_impl->activeWidget->UiState("active");
	}
}

void ruiDocument::ProcessMouseMotionEvent(ruiMouseEvent& event){
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

void ruiDocument::ProcessMouseUpEvent(ruiMouseEvent& event){
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

void ruiDocument::ProcessMouseWheelEvent(ruiMouseEvent& event){
	if (_impl->activeWidget){
		_impl->activeWidget->Trigger(ruiEVT_MOUSE_WHEEL, event);
	}
}

uint32_t ruiDocument::RunEveryUpdate(UpdateFunc func){
	uint32_t handle = _impl->updateFuncHandle++;
	_impl->everyUpdateFuncs[handle] = func;

	return handle;
}

uint32_t ruiDocument::RunNextUpdate(UpdateFunc func){
	uint32_t handle = _impl->updateFuncHandle++;
	_impl->nextUpdateFuncs[handle] = func;

	return handle;
}

void ruiDocument::ClearRunEveryUpdate(int handle) {
	_impl->everyUpdateFuncs.erase(handle);
}

void ruiDocument::ClearNextUpdate(int handle){
	_impl->nextUpdateFuncs.erase(handle);
}