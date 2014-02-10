#include "rDemoModule.hpp"

void rDemoModule::Update(rEngine& engine){
	m_pawn->Update(engine);
	m_camera->Update(engine);

	m_controller->OnUpdate(engine);
}

void rDemoModule::Draw(rEngine& engine){
	engine.renderer->Render(m_viewport);
	m_controller->OnDraw(engine);
}

void rDemoModule::Init(rEngine& engine){
	InitView(engine);
	LoadContent(engine);
}

void rDemoModule::InitView(rEngine& engine){
	rSize displaySize = engine.application->DisplaySize();

	m_camera = new rDemoCamera("camera", rVector3(0,1,5));
	m_viewport.SetCamera(m_camera);
	m_viewport.SetClipping(0.5,1000);
	m_viewport.SetSize(displaySize);
	m_viewport.SetViewportType(rVIEWPORT_PERSP);
}

void rDemoModule::LoadContent(rEngine& engine){
	engine.content->AddListener(new rLogContentListener());
	rLog::Info("Loading Assets");

	engine.content->LoadAssetManifestFromPath("content/manifest.xml");

	rLog::Info("Loading Complete");

	m_pawn = new rPawn(NULL, "pawn" , rVector3::ZeroVector);
}

void rDemoModule::Uninit(rEngine& engine){
}

void rDemoModule::InitUI(ruiLayoutManager& uiManager, rEngine& engine){
	ruiOverlay* overlay = uiManager.CreateOverlay(&m_viewport);

	m_controller = new ruiDemoController(engine.content, m_pawn, m_camera); 
	m_controller->Init(overlay);
}
