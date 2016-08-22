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

void ModelViewerModule::Init(const rArrayString& args) {
	auto fileSystemRed = _engine->content->FileSystem()->GetReadFileRef(args[0]);
	ModelData modelData;
	modelData.Read(*fileSystemRed);
	Model* model =_engine->content->Models()->LoadFromData(modelData, "suv");
	rAlignedBox3 boundingBox = model->GetBoundingBox();
	rVector3 center = boundingBox.Center();

	rProp* prop = new rProp(model, "prop", _engine);
	_engine->scene->AddActor(prop);

	rViewport* mainViewport = _engine->component->CreateViewport("main");
	mainViewport->SetFarClip(500);

	rDemoCamera* camera = new rDemoCamera("main", _engine);
	camera->Reset(center, 150, 0, 0);
	mainViewport->SetCamera(camera);
	_engine->scene->AddActor(camera);
}

void ModelViewerModule::LoadScene(const rString& sceneName) {

}

void ModelViewerModule::DeleteActor(rActor3* actor) {

}

void ModelViewerModule::AfterRenderScene(rViewport* viewport) {

}