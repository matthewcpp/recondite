#include "rAndroidApplication.hpp"

rAndroidApplication::rAndroidApplication(){
	m_log = NULL;
	m_contentManager = NULL;
	m_inputManager = NULL;
	m_graphicsDevice = NULL;

	m_renderer = NULL;
	m_camera = NULL;
}

rAndroidApplication::~rAndroidApplication(){

}

bool rAndroidApplication::Init(struct android_app* state){
	m_log = new rAndroidLog();
	rLog::SetLogTarget(engine->log);

	m_graphicsDevice = new rOpenGLGraphicsDevice();

    AAssetManager* assetManager = state->activity->assetManager;
    m_contentManager = new rAndroidContentManager(assetManager, m_graphicsDevice);

    engine->inputManager = new rAndroidInputManager();

	TempInit();

	return true;
}

int32_t rAndroidApplication::OnInput(AInputEvent* event){
	m_inputManager->ProcessInputEvent(event);

	return 1;
}

void rAndroidApplication::Draw(){
	m_graphicsDevice->Clear();
	m_graphicsDevice->SetActiveViewport(&m_viewport);

	m_graphicsDevice->SwapBuffers();
}

void rAndroidApplication::ProcessCommand(int32_t cmd){
	switch (cmd){
	case APP_CMD_SAVE_STATE:
		OnSaveStateCommand;
		break;

	case APP_CMD_INIT_WINDOW:
		OnInitWindowCommand();
		break;

	case APP_CMD_TERM_WINDOW:
		OnTerminateWindowCommand();
		break;

	case APP_CMD_GAINED_FOCUS:
		OnApplicationGainFocusCommand();
		break;

	case APP_CMD_LOST_FOCUS:
		OnApplicationLostFocusCommand();
		break;
	};
}

void rAndroidApplication::OnSaveStateCommand(){
	rLog::Info("Application Save State Command");
}

void rAndroidApplication::OnInitWindowCommand(){
	rLog::Info("Application Init Window Command");
}

void rAndroidApplication::OnTerminateWindowCommand(){
	rLog::Info("Application Terminate Window Command");
}

void rAndroidApplication::OnApplicationGainFocusCommand(){
	rLog::Info("Application Gain Focus Command");
}

void rAndroidApplication::OnApplicationLostFocusCommand(){
	rLog::Info("Application Lost Focus Command");
}

void rAndroidApplication::TempInit(){
	m_camera = new rTargetCamera("camera", rVector3(0,0,50));
	m_camera->SetTarget(rVector3(0,0,-5));

	viewport.SetCamera(engine->camera);
	viewport.SetClipping(1.0, 100.0f);
	viewport.SetSize(w,h);
	viewport.SetViewportType(rVIEWPORT_PERSP);

	m_renderer = new rRenderer(m_graphicsDevice);
}
