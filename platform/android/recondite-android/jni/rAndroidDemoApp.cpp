#include"rAndroidDemoApp.hpp"

rAndroidDemoApp::rAndroidDemoApp(){
	m_frame = 0;
	rot = 0;

	m_uiController = NULL;
}

void rAndroidDemoApp::Update(){
	if (m_started){
		rot += 1.0f;

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

		DrawImmediate();

		m_graphicsDevice->SwapBuffers();
		m_frame++;
	}
}

bool rAndroidDemoApp::Init(android_app* state){
	bool result = rAndroidApplication::Init(state);

	if (result){
		m_layoutManager = new ruiLayoutManager();
		ruiWidget::widgetManager = m_layoutManager;

		m_uiController = new ruiDemoController(m_inputManager->CreateController(1,1,1,2));
		m_uiController->Init(m_layoutManager);

		m_inputManager->AddListener(m_layoutManager);

		rLog::Info("Init demo assets");

		m_contentManager->LoadFontFromPath("Consolas.rfnt", "consolas");
		rModel* reindeer = m_contentManager->LoadModelFromPath("reindeer.rmdl", "reindeer");

		if (reindeer){
			rSkeleton* skeleton = reindeer->Skeleton();
			ruiPicker* picker = (ruiPicker*)m_layoutManager->GetWidget(102);

			rArrayString animations;
			skeleton->GetAnimationNames(animations);
			picker->SetOptions(animations);
		}

		m_viewport.SetClipping(1,1000);

		rLog::Info("Demo assets loaded");
	}

	return result;
}

#include <sstream>

void rAndroidDemoApp::DrawImmediate(){
	m_graphicsDevice->EnableDepthTesting(true);

	rModel* model = m_contentManager->GetModelAsset("reindeer");

	if (model){
		rMatrix4 transform;
		transform.SetTranslate(0,-1,0);
		m_renderer->RenderModel(model, transform);
	}

	m_graphicsDevice->EnableDepthTesting(false);

	m_layoutManager->Draw(m_engine);
}
