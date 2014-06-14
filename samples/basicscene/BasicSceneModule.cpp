#include "BasicSceneModule.hpp"

void BasicSceneModule::BeforeUpdateScene(rEngine& engine){
	rOStringStream str;
	rVector3 pos = m_camera->Position();

	str << "camera: " << pos.x << ", " << pos.y << ", " << pos.z;

	m_textCameraPos->SetText(str.Str());

	float distance = 10 * engine.time.TimeDeltaSeconds();

	if (engine.input->Keyboard()->GetKeyState('w') == rKEY_DOWN){
		m_camera->MoveForward(distance);
	}
	else if (engine.input->Keyboard()->GetKeyState('s') == rKEY_DOWN){
		m_camera->MoveBackward(distance);
	}
}

void BasicSceneModule::AfterUpdateScene(rEngine& engine){
}

void BasicSceneModule::BeforeRenderScene(rViewInfo& view, rEngine& engine){
}

void BasicSceneModule::AfterRenderScene(rViewInfo& view, rEngine& engine){
	rOStringStream str;
	ruiText* renderInfo = (ruiText*)view.overlay->GetWidget(2);
	size_t actorCount = engine.scene->NumActors();
	size_t renderCount = engine.renderer->ObjectsRendered();

	str << "Rendered: " << renderCount <<'/' << actorCount << " actors";
	renderInfo->SetText(str.Str());
}

void BasicSceneModule::BeforeRenderOverlay(rViewInfo& view, rEngine& engine){
}

void BasicSceneModule::AfterRenderOverlay(rViewInfo& view, rEngine& engine){
}

void BasicSceneModule::Init(rEngine& engine){
	rSize displaySize = engine.application->DisplaySize();

	rViewport* viewport = engine.application->CreateViewport("main");
	viewport->SetClipping(0.5,1000);
	viewport->SetSize(displaySize);
	viewport->SetViewportType(rVIEWPORT_PERSP);

	m_camera = new rViewCamera("camera", rVector3::ZeroVector);
	viewport->SetCamera(m_camera);

	engine.content->LoadFontFromPath("content/fonts/Consolas.rfnt", "consolas");
}

void BasicSceneModule::InitUI(ruiOverlayManager& manager, rEngine& engine){
	ruiOverlay* overlay = manager.CreateOverlay(engine.application->GetViewport("main"));
	m_textCameraPos = new ruiText(1, rPoint(10,10), rSize(500,35));
	overlay->AddWidget(m_textCameraPos);

	overlay->AddWidget(new ruiText(2, rPoint(10,50), rSize(500,35)));
}

void BasicSceneModule::Uninit(rEngine& engine){
}

void BasicSceneModule::LoadScene(const rString& sceneName, rEngine& engine){
}

void BasicSceneModule::DeleteActor(rActor3* actor){
}