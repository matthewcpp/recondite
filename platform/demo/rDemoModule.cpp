#include "rDemoModule.hpp"

void rDemoModule::Update(rEngine& engine){
}

void rDemoModule::Draw(rEngine& engine){
	engine.renderer->Render(m_viewport);

	rAlignedBox3 box(-1,-1,-1, 1, 1, 1);

	engine.renderer->RenderWireBox(box, rColor::White);
}

void rDemoModule::Init(rEngine& engine){
	InitView(engine);
	LoadContent(engine);
}

void rDemoModule::InitView(rEngine& engine){
	m_camera = new rViewCamera("camera", rVector3(0,0,5));
	m_viewport.SetCamera(m_camera);
	m_viewport.SetClipping(1,1000);
	m_viewport.SetSize(640,480);
	m_viewport.SetViewportType(rVIEWPORT_PERSP);
}

void rDemoModule::LoadContent(rEngine& engine){
	rFontData fontData;
	fontData.LoadFromFile("assets/", "Consolas");
	rFont* font = engine.content->LoadFont(fontData, "consolas");
}

void rDemoModule::Uninit(rEngine& engine){
}

void rDemoModule::InitUI(ruiLayoutManager& uiManager, rEngine& engine){
	ruiOverlay* overlay = uiManager.CreateOverlay(&m_viewport);

	ruiPicker* picker = new ruiPicker(100, rPoint(25,10), rSize(250, 35));
	picker->AddOption("item 1");
	picker->AddOption("item 2");
	overlay->AddWidget(picker);
}