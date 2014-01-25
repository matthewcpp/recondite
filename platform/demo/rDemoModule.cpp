#include "rDemoModule.hpp"

void rDemoModule::Update(rEngine& engine){
	m_pawn->Update(engine);

	m_controller->OnUpdate(engine);
}

void rDemoModule::Draw(rEngine& engine){
	engine.renderer->Render(m_viewport);

	m_pawn->Draw(engine);

	m_controller->OnDraw(engine);
}

void rDemoModule::Init(rEngine& engine){
	InitView(engine);
	LoadContent(engine);
}

void rDemoModule::InitView(rEngine& engine){
	rSize displaySize = engine.application->DisplaySize();

	m_camera = new rViewCamera("camera", rVector3(0,1,5));
	m_viewport.SetCamera(m_camera);
	m_viewport.SetClipping(1,1000);
	m_viewport.SetSize(displaySize);
	m_viewport.SetViewportType(rVIEWPORT_PERSP);
}

void rDemoModule::LoadContent(rEngine& engine){
	rFont* font = engine.content->LoadFontFromPath("assets/consolas.rfnt", "consolas");
	rModel* model = NULL;
	model = engine.content->LoadModelFromPath("assets/reindeer.rmdl", "reindeer");
	model = engine.content->LoadModelFromPath("assets/chicken.rmdl", "chicken");
	model = engine.content->LoadModelFromPath("assets/cat.rmdl", "cat");
	model = engine.content->LoadModelFromPath("assets/turtle.rmdl", "turtle");

	m_pawn = new rPawn(model, "pawn" , rVector3::ZeroVector);
}

void rDemoModule::Uninit(rEngine& engine){
}

void rDemoModule::InitUI(ruiLayoutManager& uiManager, rEngine& engine){
	ruiOverlay* overlay = uiManager.CreateOverlay(&m_viewport);

	m_controller = new ruiDemoController(engine.content, m_pawn); 
	m_controller->Init(overlay);
}
