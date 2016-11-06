#include "ui/ruiDocument.hpp"

#include <map>
#include <vector>

#include "ui/ruiWidget.hpp"
#include "ui/ruiLayout.hpp"
#include "stream/rOStringStream.hpp"
#include "ui/ruiMenuManager.hpp"

struct ruiDocument::Impl{
	std::vector<std::unique_ptr<ruiWidget>> widgets;
	std::multimap<rString, ruiWidget*> widgetsByName;

	std::map<uint32_t, UpdateFunc> everyUpdateFuncs;
	std::map<uint32_t, UpdateFunc> nextUpdateFuncs;
	uint32_t updateFuncHandle;

	ruiWidget* activeWidget;
	ruiWidget* modalWidget;
	ruiWidget* focusedWidget;
	ruiLayout* layout;
	rViewport* viewport;
	ruiController* controller;

	ruiStyleManager styleManager;
	ruiMenuManager menuManager;

	bool layoutNeedsUpdate;

	Impl(rEngine* _engine, rViewport* _viewport)
		:activeWidget(nullptr), viewport(_viewport), menuManager(_engine), controller(nullptr), updateFuncHandle(1), layoutNeedsUpdate(false){}
};

ruiDocument::ruiDocument(rEngine* engine, rViewport* viewport){
	_impl = new Impl(engine, viewport);

	_impl->activeWidget = nullptr;
	_impl->focusedWidget = nullptr;
	_impl->layout = nullptr;
	_impl->viewport = viewport;
}

ruiDocument::~ruiDocument(){
	delete _impl;
}

void ruiDocument::WidgetUpdated(ruiWidget* widget){
	_impl->layoutNeedsUpdate = true;
}

void ruiDocument::AddWidget(ruiWidget* widget){
	_impl->widgets.emplace_back(widget);
	_impl->widgetsByName.insert(std::make_pair(widget->Id(), widget));

	_impl->layoutNeedsUpdate = true;
}

ruiWidget* ruiDocument::GetActiveWidget() {
	return _impl->activeWidget;
}

ruiWidget* ruiDocument::GetWidgetById(const rString& id){
	auto result = _impl->widgetsByName.equal_range(id);

	if (result.first != result.second)
		return result.first->second;
	else
		return nullptr;
}

void ruiDocument::Update(){
	for (auto& item : _impl->everyUpdateFuncs){
		item.second();
	}

	for (auto& item : _impl->nextUpdateFuncs){
		item.second();
	}

	_impl->nextUpdateFuncs.clear();

	if (_impl->layout)
		_impl->layout->Update();

	UpdateLayout();
}

void ruiDocument::UpdateLayout(bool force){
	if (_impl->layoutNeedsUpdate && _impl->layout){
		rRect layoutRect = _impl->viewport->GetScreenRect();
		_impl->layout->Layout(layoutRect);
		_impl->layoutNeedsUpdate = false;
    }
}

void ruiDocument::Draw(){
	if (_impl->layout)
		_impl->layout->Draw();

	_impl->menuManager.Draw();
}

void ruiDocument::Clear(){
	_impl->widgets.clear();
	_impl->widgetsByName.clear();

	_impl->layoutNeedsUpdate = true;
	_impl->activeWidget = nullptr;
	_impl->focusedWidget = nullptr;
	_impl->layout = nullptr;
}

ruiWidget* ruiDocument::SelectWidget(const rPoint& position){
	rRect boundingBox;
	ruiWidget* widget;

	for (size_t i = _impl->widgets.size()-1; i > 0; i--) {
		widget = _impl->widgets[i].get();
		boundingBox = widget->BoundingBox();

		if (boundingBox.ContainsPoint(position)){
			return widget;
		}
	}

	return nullptr;
}

rViewport* ruiDocument::GetViewport() {
	return _impl->viewport;
}

ruiLayout* ruiDocument::Layout() const{
	return _impl->layout;
}

void ruiDocument::SetLayout(ruiLayout* layout){
	_impl->layout = layout;
	_impl->layoutNeedsUpdate = true;
}

rString ruiDocument::GetDefaultId () const{
	rOStringStream str("item");
	str << _impl->widgetsByName.size();

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

	rPoint position = event.Position();
	_impl->focusedWidget = SelectWidget(position);

	if (_impl->activeWidget){
		_impl->activeWidget->Trigger(ruiEVT_MOUSE_DOWN, event);
		_impl->activeWidget->UiState("active");
	}
}

void ruiDocument::ProcessMouseMotionEvent(ruiMouseEvent& event){
	rPoint position = event.Position();
	ruiWidget* selectedWidget = SelectWidget(position);

	if (_impl->activeWidget){

		if (selectedWidget == _impl->activeWidget) {
			_impl->activeWidget->Trigger(ruiEVT_MOUSE_MOTION, event);
		}
		else {
			_impl->activeWidget->Trigger(ruiEVT_MOUSE_LEAVE, event);
			_impl->activeWidget->UiState("");
			_impl->activeWidget = nullptr;
		}
	}
	
	if (selectedWidget){
		selectedWidget->UiState("hover");
		_impl->activeWidget = selectedWidget;
		selectedWidget->Trigger(ruiEVT_MOUSE_ENTER, event);
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

void ruiDocument::ProcessKeyDownEvent(ruiKeyEvent& event){
	if (_impl->focusedWidget)
		_impl->focusedWidget->Trigger(ruiEVT_KEY_DOWN, event);
}

void ruiDocument::ProcessKeyUpEvent(ruiKeyEvent& event){
	if (_impl->focusedWidget)
		_impl->focusedWidget->Trigger(ruiEVT_KEY_UP, event);
}