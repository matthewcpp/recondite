#include "ModelViewerModule.hpp"
#include "ModelViewerController.hpp"

#include "rCamera.hpp"
#include "rProp.hpp"

ruiController* CreateUiController(const rString& name, rEngine* engine, ruiDocument* document) {
	return new ModelViewerController(name, engine, document);
}

void DeleteUiController(ruiController* controller) {
	delete controller;
}

ModelViewerModule::ModelViewerModule(rEngine* engine)
	:rModule("User Interface Sample") 
{
	_engine = engine;
}

void ModelViewerModule::Init() {
	auto fileSystemRed = _engine->content->FileSystem()->GetReadFileRef("C:/temp/assets/suv.rmdl");
	ModelData modelData;
	modelData.Read(*fileSystemRed);
	Model* model =_engine->content->Models()->LoadFromData(modelData, "suv");
	rAlignedBox3 boundingBox = model->GetBoundingBox();
	rVector3 center = boundingBox.Center();

	rProp* prop = new rProp(model, "prop", _engine);
	_engine->scene->AddActor(prop);

	rViewport* mainViewport = _engine->component->CreateViewport("main");
	mainViewport->SetFarClip(500);

	rCamera* camera = new rCamera("main", _engine);
	camera->SetPosition(center.x, center.y, boundingBox.max.z* 3);
	camera->SetTarget(center);
	mainViewport->SetCamera(camera);
}

void ModelViewerModule::LoadScene(const rString& sceneName) {

}

void ModelViewerModule::DeleteActor(rActor3* actor) {

}

void ModelViewerModule::AfterRenderScene(rViewport* viewport) {

}