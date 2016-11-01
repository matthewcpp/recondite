#include "ModelViewerModule.hpp"
#include "ModelViewerController.hpp"
#include "rDemoCamera.hpp"

#include "rCamera.hpp"
#include "rProp.hpp"

ruiController* CreateUiController(const rString& name, rEngine* engine, ruiDocument* document) {
	return new ModelViewerController(name, engine, document);
}

void DeleteUiController(ruiController* controller) {
	delete controller;
}

ModelViewerModule::ModelViewerModule(rEngine* engine)
	:rModule("Model Viewer Sample") 
{
	_engine = engine;
}

rViewport* CreateView(Model* model, rEngine* engine) {
	rViewport* mainViewport = engine->component->CreateViewport("main");

	rAlignedBox3 boundingBox = model->GetBoundingBox();
	rVector3 center = boundingBox.Center();

	rDemoCamera* camera = new rDemoCamera("main", engine);
	engine->scene->AddActor(camera);
	mainViewport->SetCamera(camera);

	//set up decent clipping values
	rAlignedBox3 box = model->GetBoundingBox();
	
	float diagonal = box.min.Distance(box.max);
	camera->Reset(center, diagonal * 3, 0, 0);

	mainViewport->SetFarClip(diagonal * 10);

	rVector3 delta = (box.max - box.min) / 15.0;
	float nearClip = delta.x;
	nearClip = std::min(nearClip, delta.y);
	nearClip = std::min(nearClip, delta.z);
	mainViewport->SetNearClip(nearClip);

	return mainViewport;
}

void ModelViewerModule::Init(const rArrayString& args) {
	_engine->ui->RegisterControllerClass("ModelViewerController", &CreateUiController, &DeleteUiController);

	auto fileSystemRed = _engine->content->FileSystem()->GetReadFileRef(args[0]);
	ModelData modelData;
	modelData.Read(*fileSystemRed);
	Model* model =_engine->content->Models()->LoadFromData(modelData, "model");
	
	rProp* prop = new rProp(model, "prop", _engine);
	_engine->scene->AddActor(prop);

	rViewport* mainViewport = CreateView(model, _engine);

	_engine->ui->LoadUiDocument("C:/development/recondite/samples/modelviewer/modelviewer/modelviewer.xml", mainViewport);
}

void ModelViewerModule::LoadScene(const rString& sceneName) {

}

void ModelViewerModule::DeleteActor(rActor3* actor) {

}

void ModelViewerModule::AfterRenderScene(rViewport* viewport) {

}