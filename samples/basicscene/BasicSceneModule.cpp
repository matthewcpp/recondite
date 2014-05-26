#include "BasicSceneModule.hpp"

void BasicSceneModule::Update(rEngine& engine){
}

void BasicSceneModule::Draw(rEngine& engine){
}

void BasicSceneModule::Init(rEngine& engine){
	rSize displaySize = engine.application->DisplaySize();

	rViewport* viewport = engine.application->CreateViewport("main");
	viewport->SetClipping(0.5,1000);
	viewport->SetSize(displaySize);
	viewport->SetViewportType(rVIEWPORT_PERSP);

	rViewCamera* viewCamera = new rViewCamera("camera", rVector3::ZeroVector);
	viewport->SetCamera(viewCamera);
}

void BasicSceneModule::InitUI(ruiOverlayManager& manager, rEngine& engine){
}

void BasicSceneModule::Uninit(rEngine& engine){
}

void BasicSceneModule::LoadScene(const rString& sceneName, rEngine& engine){
}

void BasicSceneModule::DeleteActor(rActor3* actor){
}