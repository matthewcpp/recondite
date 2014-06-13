#include "rDemoModule.hpp"

void rDemoModule::Update(rEngine& engine){
	m_camera->Update(engine);

	m_controller->OnUpdate(engine);
}

void rDemoModule::Draw(rEngine& engine){
	m_controller->OnDraw(engine);
}

void rDemoModule::Init(rEngine& engine){
	InitView(engine);
	LoadContent(engine);
}

void rDemoModule::InitView(rEngine& engine){
	rSize displaySize = engine.application->DisplaySize();
	m_viewport = engine.application->CreateViewport("main");

	m_camera = new rDemoCamera("camera", rVector3(0,1,5));
	m_viewport->SetCamera(m_camera);
	m_viewport->SetClipping(0.5,1000);
	m_viewport->SetSize(displaySize);
	m_viewport->SetViewportType(rVIEWPORT_PERSP);
}

void rDemoModule::LoadContent(rEngine& engine){
	engine.content->AddListener(new rLogContentListener());
	rLog::Info("Loading Assets");

	engine.content->LoadAssetManifestFromPath("content/manifest.xml");

	rLog::Info("Loading Complete");
}

void rDemoModule::LoadScene(const rString& sceneName, rEngine& engine){
	m_pawn = new rDemoPawn(NULL, "pawn" , rVector3::ZeroVector);
	engine.scene->AddActor(m_pawn);

	//m_pawn->AnimationPlayer()->SetAnimationSpeed(0.25f);
	m_controller->SetPawn(m_pawn);

	rArrayString models;
	engine.content->GetModelNames(models);

	if (models.size() > 0)
		m_controller->SetActiveModel(models[0]);
}

void rDemoModule::Uninit(rEngine& engine){
}

void rDemoModule::InitUI(ruiOverlayManager& uiManager, rEngine& engine){
	ruiOverlay* overlay = uiManager.CreateOverlay(m_viewport);

	m_controller = new ruiDemoController(engine.content, m_camera); 
	m_controller->Init(overlay);
}


void rDemoModule::DeleteActor(rActor3* actor){
	delete actor;
}