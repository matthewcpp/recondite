#include"rAndroidDemoApp.hpp"

rAndroidDemoApp::rAndroidDemoApp(){
	m_frame = 0;
	rot = 0;
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
		rController* controller = m_inputManager->CreateController(1,1,1,2);

		m_layoutManager = new ruiLayoutManager();

		m_inputManager->AddListener(m_layoutManager);

		m_layoutManager->AddWidget(new ruiDPad(controller->DPad(0), 100, rPoint(700, 300), rSize(300, 300)));
		m_layoutManager->AddWidget(new ruiPicker(m_layoutManager, 102, rPoint(25,10), rSize(250, 35)));
		m_layoutManager->AddWidget(new ruiSlider(101, rPoint(25,75), rSize(250, 35)));
		m_layoutManager->AddWidget(new ruiButton("click me", 666, rPoint(25, 120), rSize(175, 40)));
		m_layoutManager->AddWidget(new ruiCheckbox(667, rPoint(25, 195), rSize(50, 50)));
		m_layoutManager->AddWidget(new ruiText("Hello Android, How R U?\nDroid Does.", 900, rPoint(25, 275), rSize(200, 150)));

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
