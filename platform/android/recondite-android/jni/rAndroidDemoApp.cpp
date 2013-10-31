#include"rAndroidDemoApp.hpp"

rAndroidDemoApp::rAndroidDemoApp(){
	m_frame = 0;
	rot = 0;
}

void rAndroidDemoApp::Update(){
	if (m_started){
		rot += 1.0f;
		m_dpad->Update(m_engine);
		m_analogStick->Update(m_engine);

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
		rLog::Info("Init demo assets");

		m_contentManager->LoadFontFromPath("Consolas.rfnt", "consolas");
		m_contentManager->LoadModelFromAsset("reindeer.rmdl", "reindeer");

		rController* controller = m_inputManager->CreateController(1,1,1,2);
		m_dpad = new ruiDPad(controller->DPad(0), 100, rPoint(30, 300), rSize(300, 300));
		m_analogStick = new ruiAnalogStick(controller, 0, 101, rPoint(700, 300), rSize(300, 300));

		m_viewport.SetClipping(1,1000);
	}

	return result;
}

void rAndroidDemoApp::DrawImmediate(){
	m_graphicsDevice->EnableDepthTesting(true);
	rModel* model = m_contentManager->GetModelAsset("reindeer");

	rMatrix4 transform;
	transform.SetTranslate(0,-1,0);
	transform.SetRotationY(rot);

	if (model){
		m_renderer->RenderModel(model, transform);
	}

	m_graphicsDevice->EnableDepthTesting(false);


	if (model){
		rColor skeletonColor(255,255,255,255);
		m_renderer->RenderSkeleton(model->Skeleton(), transform, skeletonColor);
	}


	m_dpad->Draw(m_renderer);
	//m_analogStick->Draw(m_renderer);

	rFont* font = m_contentManager->GetFontAsset("consolas");

	if (font){
		rPoint pos(300,300);
		rColor color(233,48,159,255);

		m_renderer->RenderString("i like turtles", font, pos, color);
	}
}
