#include "ui/ruiManager.hpp"
#include "ui/ruiDocumentLoader.hpp"

struct ruiControllerClassDescription{
	ruiIManager::ControllerCreateFunction createFunc;
	ruiIManager::ControllerDeleteFunction deleteFunc;

	ruiControllerClassDescription(){}
	ruiControllerClassDescription(ruiIManager::ControllerCreateFunction createf, ruiIManager::ControllerDeleteFunction deletef)
	:createFunc(createf), deleteFunc(deletef){}
};

struct ruiManager::Impl{
	rEngine* engine;

	std::map<rViewport*, ruiDocument*> documents;
	std::map<rString, ruiControllerClassDescription> controllerMap;

	Impl(rEngine* _engine) : engine(_engine){}

	bool ProcessMouseDown(rMouseButton button, const rPoint& position);
	bool ProcessMouseUp(rMouseButton button, const rPoint& position);

	rViewport* DetermineViewport(const rPoint& point);
	ruiDocument* DetermineDocument(const rPoint& point);
	void AddDocumentToViewport(ruiDocument* document, rViewport* viewport);
};

ruiManager::ruiManager(rEngine* engine){
	_impl = new Impl(engine);
}

ruiManager::~ruiManager(){
	Clear();
	delete _impl;
}

ruiDocument* ruiManager::CreateUiDocument(rViewport* viewport){

	ruiDocument* docuement = new ruiDocument(_impl->engine, viewport);
	_impl->AddDocumentToViewport(docuement, viewport);

	return docuement;
}

ruiDocument* ruiManager::LoadUiDocument(const rString& filePath, rViewport* viewport){
	ruiDocumentLoader loader(this, _impl->engine);
	ruiDocument* document = loader.LoadDocument(filePath, viewport);

	if (document){
		_impl->AddDocumentToViewport(document, viewport);
		document->UpdateLayout(true);

		ruiController* controller = document->GetController();
		if (controller)
			controller->OnDocumentLoaded();

		return document;
	}
	else {
		return NULL;
	}
}

void ruiManager::Impl::AddDocumentToViewport(ruiDocument* document, rViewport* viewport){
	auto result = documents.find(viewport);

	if (result != documents.end()){
		delete result->second;
	}

	documents[viewport] = document;
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

ruiController* ruiManager::CreateController(const rString& name, ruiDocument* document){
	auto result = _impl->controllerMap.find(name);

	if (result == _impl->controllerMap.end()){
		return nullptr;
	}
	else{
		return result->second.createFunc(name, _impl->engine, document);
	}
}

void ruiManager::Clear(){
	auto end = _impl->documents.end();

	for (auto it = _impl->documents.begin(); it != end; ++it){
		delete it->second;
	}

	_impl->documents.clear();
}

rViewport* ruiManager::Impl::DetermineViewport(const rPoint& point){
	auto end = documents.end();

	for (auto it = documents.begin(); it != end; ++it){
		rRect screenRect = it->first->GetScreenRect();

		if (screenRect.ContainsPoint(point))
			return it->first;
	}

	return NULL;
}

ruiDocument* ruiManager::Impl::DetermineDocument(const rPoint& point){
	rViewport* viewport = DetermineViewport(point);

	if (viewport && documents.count(viewport))
		return documents[viewport];
	else
		return NULL;
}

ruiDocument* ruiManager::GetUiDocument(rViewport* viewport) const{
	auto result = _impl->documents.find(viewport);

	if (result != _impl->documents.end())
		return result->second;
	else
		return NULL;
}

void ruiManager::Update(){
	auto end = _impl->documents.end();

	for (auto it = _impl->documents.begin(); it != end; ++it){
		it->second->Update();
	}
}

void ruiManager::Draw(rViewport* viewport){
	if (_impl->documents.count(viewport)){
		_impl->documents[viewport]->Draw();
	}
}
bool ruiManager::InsertKeyEvent(rKey key, rKeyState state){
	ruiDocument* document = _impl->DetermineDocument(_impl->engine->input->GetMouseState()->Position());

	ruiKeyEvent keyEvent(key, state);

	if (state == rKEY_DOWN)
		document->ProcessKeyDownEvent(keyEvent);
	else{
		document->ProcessKeyUpEvent(keyEvent);
	}

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
	ruiDocument* document = DetermineDocument(position);

	if (document){
		ruiMouseEvent event(button, rBUTTON_STATE_DOWN, position);
		document->ProcessMouseDownEvent(event);
		return event.Handled();
	}
	else{
		return false;
	}
}

bool ruiManager::InsertMouseMotionEvent(const rPoint& position){
	ruiDocument* document = _impl->DetermineDocument(position);

	if (document){
		ruiMouseEvent event(position);
		document->ProcessMouseMotionEvent(event);
		return event.Handled();
	}
	else{
		return false;
	}
}

bool ruiManager::Impl::ProcessMouseUp(rMouseButton button, const rPoint& position){
	ruiDocument* document = DetermineDocument(position);

	if (document){
		ruiMouseEvent event(button, rBUTTON_STATE_UP, position);
		document->ProcessMouseUpEvent(event);
		return event.Handled();
	}
	else{
		return false;
	}
}

bool ruiManager::InsertMouseWheelEvent(const rPoint& position, rMouseWheelDirection direction){
	ruiDocument* document = _impl->DetermineDocument(position);

	if (document){
		ruiMouseEvent event(direction, position);
		document->ProcessMouseWheelEvent(event);
		return event.Handled();
	}
	else{
		return false;
	}
}