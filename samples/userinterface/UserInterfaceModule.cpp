#include "UserInterfaceModule.hpp"

#include "UserInterfaceController.hpp"

#include "rCamera.hpp"
#include "primitive/rPrimitiveBox.hpp"
#include "primitive/rPrimitiveGrid.hpp"
#include "primitive/rPrimitiveCylinder.hpp"
#include "primitive/rPrimitiveCone.hpp"
#include "primitive/rPrimitiveSphere.hpp"

ruiController* CreateUiController(const rString& name, rEngine* engine, ruiDocument* document){
	return new UserInterfaceController(name, engine, document);
}

void DeleteUiController(ruiController* controller){
	delete controller;
}


UserInterfaceModule::UserInterfaceModule(rEngine* engine)
	:rModule("User Interface Sample")
{
	_engine = engine;
}

void UserInterfaceModule::Init(const rArrayString& args) {
	_engine->ui->RegisterControllerClass("UserInterfaceController", &CreateUiController, &DeleteUiController);
	rViewport* mainViewport = _engine->component->CreateViewport("main");

	rCamera* camera = new rCamera("main", _engine);
	camera->SetPosition(0, 6, 10);
	camera->SetTarget(rVector3::ZeroVector);
	mainViewport->SetCamera(camera);

	rPrimitiveBox* box = new rPrimitiveBox("Box", _engine);
	box->SetFaceColor(rColor::Green);
	box->SetRotation(rVector3(0, 25, 0));
	_engine->scene->AddActor(box);

	rPrimitiveGrid* grid = new rPrimitiveGrid("Plane", _engine);
	grid->SetColumns(1);
	grid->SetRows(1);
	grid->RenderingOptions()->SetVisibility(false);
	_engine->scene->AddActor(grid);

	rPrimitiveCylinder* cylinder = new rPrimitiveCylinder("Cylinder", _engine);
	cylinder->RenderingOptions()->SetVisibility(false);
	_engine->scene->AddActor(cylinder);

	rPrimitiveCone* cone = new rPrimitiveCone("Cone", _engine);
	cone->RenderingOptions()->SetVisibility(false);
	_engine->scene->AddActor(cone);

	rPrimitiveSphere* sphere = new rPrimitiveSphere("Sphere", _engine);
	sphere->RenderingOptions()->SetVisibility(false);
	_engine->scene->AddActor(sphere);
	

	_engine->ui->LoadUiDocument("C:/development/recondite/samples/userinterface/userinterface/userinterface.xml", mainViewport);
}

void UserInterfaceModule::AfterRenderScene(rViewport* viewInfo){

}

void UserInterfaceModule::LoadScene(const rString& sceneName) {

}

void UserInterfaceModule::DeleteActor(rActor3* actor) {
	delete actor;
}