#include "ui/ruiOverlay.hpp"

#include "ui/ruiWidget.hpp"
#include "ui/ruiLayout.hpp"
#include "stream/rOStringStream.hpp"

struct ruiOverlay::Impl{
	std::vector<ruiWidget*> widgets;

	ruiWidget* activeWidget;
	ruiWidget* modalWidget;
	ruiLayout* layout;
	rViewport* viewport;

	ruiStyleManager styleManager;
	ruiMenuManager menuManager;

	Impl(rEngine* _engine, rViewport* _viewport)
		:activeWidget(nullptr), viewport(_viewport), menuManager(_engine) {}
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

ruiWidget* ruiOverlay::ActiveWidget() const{
	return _impl->activeWidget;
}

void ruiOverlay::ActivateWidget(ruiWidget* widget){
	_impl->activeWidget = widget;
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

bool ruiOverlay::ShowContextMenu(ruiMenu* menu, const rPoint& position, rEventHandler* handler){
	return ShowContextMenu(menu, NULL, position, handler);
}

bool ruiOverlay::ShowContextMenu(ruiMenu* menu, ruiStyle* style, const rPoint& position, rEventHandler* handler){
	return _impl->menuManager.ShowContextMenu(menu, style, position, handler);
}

void ruiOverlay::CancelContextMenu(){
	_impl->menuManager.CancelContextMenu();
}