#include"rAndroidDemoApp.hpp"

rAndroidDemoApp::rAndroidDemoApp(){
	m_frame = 0;
	m_uiController = NULL;
}

void rAndroidDemoApp::Update(){
	if (m_started){
		rAndroidApplication::Update();

		m_uiController->OnUpdate(m_engine);
		m_layoutManager->Update(m_engine);

		UpdateCamera();
	}
}

void rAndroidDemoApp::UpdateCamera(){
	rController* controller = m_inputManager->GetController(0);
	rDPad* dp = controller->DPad(0);

	if (dp->Down().Down()){
		m_camera->MoveBackward(0.05);
	}

	if (dp->Up().Down()){
		m_camera->MoveForward(0.05);
	}

	if (dp->Left().Down()){
		m_camera->MoveLeft(0.05);
	}

	if (dp->Right().Down()){
		m_camera->MoveRight(0.05);
	}
}

void rAndroidDemoApp::Draw(){
	if (m_started){

		m_graphicsDevice->Clear();
		m_renderer->Render(m_viewport);

		m_graphicsDevice->EnableDepthTesting(true);
		m_uiController->OnDraw(m_engine);

		m_graphicsDevice->EnableDepthTesting(false);
		m_layoutManager->Draw(m_engine);

		m_graphicsDevice->SwapBuffers();
		m_frame++;
	}
}

bool rAndroidDemoApp::Init(android_app* state){
	bool result = rAndroidApplication::Init(state);

	if (result){
		m_layoutManager = new ruiLayoutManager();

		rLog::Info("Init demo assets");
		m_contentManager->LoadFontFromPath("Consolas.rfnt", "consolas");

		m_contentManager->LoadModelFromPath("reindeer.rmdl", "reindeer");
		m_contentManager->LoadModelFromPath("chicken.rmdl", "chicken");
		m_contentManager->LoadModelFromPath("turtle.rmdl", "turtle");
		m_contentManager->LoadModelFromPath("cat.rmdl", "cat");

		rLog::Info("Demo assets loaded");

		m_inputManager->AddListener(m_layoutManager);
		ruiWidget::widgetManager = m_layoutManager;

		m_uiController = new ruiDemoController(m_contentManager,  m_inputManager->CreateController(1,1,1,2));
		m_uiController->Init(m_layoutManager);

		m_viewport.SetClipping(1,1000);


	}

	return result;
}
