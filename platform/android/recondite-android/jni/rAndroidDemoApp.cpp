#include"rAndroidDemoApp.hpp"

rAndroidDemoApp::rAndroidDemoApp(){
	m_frame = 0;
	rot = 0;
}

void rAndroidDemoApp::Update(){
	if (m_started){
		rot += 1.0f;
		m_dpad->Update(m_engine);
		m_picker->Update(m_engine);
		m_slider->Update(m_engine);

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
		m_dpad = new ruiDPad(controller->DPad(0), 100, rPoint(700, 300), rSize(300, 300));
		m_picker = new ruiPicker(102, rPoint(10,10), rSize(250, 35));
		m_slider = new ruiSlider(101, rPoint(10,75), rSize(250, 35));

		rLog::Info("Init demo assets");

		m_contentManager->LoadFontFromPath("Consolas.rfnt", "consolas");
		rModel* reindeer = m_contentManager->LoadModelFromPath("reindeer.rmdl", "reindeer");

		rSkeleton* skeleton = reindeer->Skeleton();

		if (skeleton){
			rArrayString animations;
			skeleton->GetAnimationNames(animations);
			m_picker->SetOptions(animations);
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

	m_dpad->Draw(m_engine);
	m_picker->Draw(m_engine);
	m_slider->Draw(m_engine);
}
