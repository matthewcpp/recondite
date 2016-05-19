#include "ui/ruiManager.hpp"
#include "ui/ruiOverlayLoader.hpp"

struct ruiControllerClassDescription{
	ruiIManager::ControllerCreateFunction createFunc;
	ruiIManager::ControllerDeleteFunction deleteFunc;

	ruiControllerClassDescription(){}
	ruiControllerClassDescription(ruiIManager::ControllerCreateFunction createf, ruiIManager::ControllerDeleteFunction deletef)
	:createFunc(createf), deleteFunc(deletef){}
};

struct ruiManager::Impl{
	rEngine* engine;

	std::map<rViewport*, ruiOverlay*> overlays;
	std::map<rString, ruiControllerClassDescription> controllerMap;

	Impl(rEngine* _engine) : engine(_engine){}

	bool ProcessMouseDown(rMouseButton button, const rPoint& position);
	bool ProcessMouseUp(rMouseButton button, const rPoint& position);

	rViewport* DetermineViewport(const rPoint& point);
	ruiOverlay* DetermineOverlay(const rPoint& point);
	void AddOverlayToViewport(ruiOverlay* overlay, rViewport* viewport);
};

ruiManager::ruiManager(rEngine* engine){
	_impl = new Impl(engine);
}

ruiManager::~ruiManager(){
	Clear();
	delete _impl;
}

ruiOverlay* ruiManager::CreateOverlay(rViewport* viewport){

	ruiOverlay* overlay = new ruiOverlay(_impl->engine, viewport);
	_impl->AddOverlayToViewport(overlay, viewport);

	return overlay;
}

ruiOverlay* ruiManager::LoadOverlay(const rString& filePath, rViewport* viewport){
	ruiOverlayLoader loader(this, _impl->engine);
	ruiOverlay* overlay = loader.ParseOverlay(filePath, viewport);

	if (overlay){
		_impl->AddOverlayToViewport(overlay, viewport);
		overlay->UpdateLayout(true);

		ruiController* controller = overlay->GetController();
		if (controller)
			controller->OnOverlayLoaded();

		return overlay;
	}
	else {
		return NULL;
	}
}

void ruiManager::Impl::AddOverlayToViewport(ruiOverlay* overlay, rViewport* viewport){
	auto result = overlays.find(viewport);

	if (result != overlays.end()){
		delete result->second;
	}

	overlays[viewport] = overlay;
}

bool ruiManager::RegisterControllerClass(const rString& name, ControllerCreateFunction createFunc, ControllerDeleteFunction deleteFunc){
	if (_impl->controllerMap.count(name) == 0){
		ruiControllerClassDescription description(createFunc, deleteFunc);
		_impl->controllerMap[name] = description;

		return true;
	}
	else{
		return false;
	}

}

void ruiManager::UnregisterControllerClass(const rString& name){
	_impl->controllerMap.erase(name);
}

ruiController* ruiManager::CreateController(const rString& name, ruiOverlay* overlay){
	auto result = _impl->controllerMap.find(name);

	if (result == _impl->controllerMap.end()){
		return nullptr;
	}
	else{
		return result->second.createFunc(name, _impl->engine, overlay);
	}
}

void ruiManager::Clear(){
	auto end = _impl->overlays.end();

	for (auto it = _impl->overlays.begin(); it != end; ++it){
		delete it->second;
	}

	_impl->overlays.clear();
}

rViewport* ruiManager::Impl::DetermineViewport(const rPoint& point){
	auto end = overlays.end();

	for (auto it = overlays.begin(); it != end; ++it){
		rRect screenRect = it->first->GetScreenRect();

		if (screenRect.ContainsPoint(point))
			return it->first;
	}

	return NULL;
}

ruiOverlay* ruiManager::Impl::DetermineOverlay(const rPoint& point){
	rViewport* viewport = DetermineViewport(point);

	if (viewport && overlays.count(viewport))
		return overlays[viewport];
	else
		return NULL;
}

ruiOverlay* ruiManager::GetOverlay(rViewport* viewport) const{
	auto result = _impl->overlays.find(viewport);

	if (result != _impl->overlays.end())
		return result->second;
	else
		return NULL;
}

void ruiManager::Update(){
	auto end = _impl->overlays.end();

	for (auto it = _impl->overlays.begin(); it != end; ++it){
		it->second->Update();
	}
}

void ruiManager::Draw(rViewport* viewport){
	if (_impl->overlays.count(viewport)){
		_impl->overlays[viewport]->Draw();
	}
}
bool ruiManager::InsertKeyEvent(rKey key, rKeyState state){
	return false;
}

bool ruiManager::InsertTouchEvent(int id, const rPoint& position, rTouchType type){
	return false;
}

bool ruiManager::InsertMouseButtonEvent(rMouseButton button, rButtonState state, const rPoint& position){
	if (state == rBUTTON_STATE_DOWN)
		return _impl->ProcessMouseDown(button, position);
	else if (state ==rBUTTON_STATE_UP)
		return _impl->ProcessMouseUp(button, position);
	else
		return false;
}

bool ruiManager::Impl::ProcessMouseDown(rMouseButton button, const rPoint& position){
	ruiOverlay* overlay = DetermineOverlay(position);

	if (overlay){		
		ruiMouseEvent event(button, rBUTTON_STATE_DOWN, position);
		overlay->ProcessMouseDownEvent(event);
		return event.Handled();
	}
	else{
		return false;
	}
}

bool ruiManager::InsertMouseMotionEvent(const rPoint& position){
	ruiOverlay* overlay = _impl->DetermineOverlay(position);

	if (overlay){
		ruiMouseEvent event(position);
		overlay->ProcessMouseMotionEvent(event);
		return event.Handled();
	}
	else{
		return false;
	}
}

bool ruiManager::Impl::ProcessMouseUp(rMouseButton button, const rPoint& position){
	ruiOverlay* overlay = DetermineOverlay(position);

	if (overlay){
		ruiMouseEvent event(button, rBUTTON_STATE_UP, position);
		overlay->ProcessMouseUpEvent(event);
		return event.Handled();
	}
	else{
		return false;
	}
}

bool ruiManager::InsertMouseWheelEvent(const rPoint& position, rMouseWheelDirection direction){
	ruiOverlay* overlay = _impl->DetermineOverlay(position);

	if (overlay){
		ruiMouseEvent event(direction, position);
		overlay->ProcessMouseWheelEvent(event);
		return event.Handled();
	}
	else{
		return false;
	}
}