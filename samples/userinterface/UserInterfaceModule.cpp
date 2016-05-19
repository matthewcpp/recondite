#include "UserInterfaceModule.hpp"

#include "UserInterfaceController.hpp"

ruiController* CreateUiController(const rString& name, rEngine* engine, ruiDocument* document){
	return new UserInterfaceController(name, engine, document);
}

void DeleteUiController(ruiController* controller){
	delete controller;
}


UserInterfaceModule::UserInterfaceModule(rEngine* engine)
	:rModule("User Interface Sample"){
	_engine = engine;
}

void UserInterfaceModule::Init() {
	_engine->ui->RegisterControllerClass("UserInterfaceController", &CreateUiController, &DeleteUiController);
	rViewport* mainViewport = _engine->component->CreateViewport("main");

	_engine->ui->LoadUiDocument("C:/development/recondite/samples/userinterface/userinterface/userinterface.xml", mainViewport);
}

void UserInterfaceModule::AfterRenderScene(rViewport* viewInfo){

}

void UserInterfaceModule::LoadScene(const rString& sceneName) {

}

void UserInterfaceModule::DeleteActor(rActor3* actor) {
	delete actor;
}