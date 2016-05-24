#include "UserInterfaceModule.hpp"

#include "UserInterfaceController.hpp"

#include "rCamera.hpp"
#include "primitive/rPrimitiveBox.hpp"

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

	rCamera* camera = new rCamera("main", _engine);
	camera->SetPosition(0, 6, 10);
	camera->SetTarget(rVector3::ZeroVector);
	mainViewport->SetCamera(camera);

	rPrimitiveBox* box = new rPrimitiveBox("box", _engine);
	box->SetRotation(rVector3(0, 23.26, 0));
	_engine->scene->AddActor(box);

	_engine->ui->LoadUiDocument("C:/development/recondite/samples/userinterface/userinterface/userinterface.xml", mainViewport);
}

void UserInterfaceModule::AfterRenderScene(rViewport* viewInfo){

}

void UserInterfaceModule::LoadScene(const rString& sceneName) {

}

void UserInterfaceModule::DeleteActor(rActor3* actor) {
	delete actor;
}