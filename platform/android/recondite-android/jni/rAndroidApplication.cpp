#include "rAndroidApplication.hpp"

rAndroidApplication::rAndroidApplication(){
	m_log = NULL;
	m_contentManager = NULL;
	m_inputManager = NULL;
	m_graphicsDevice = NULL;

	m_renderer = NULL;
	m_camera = NULL;

	m_started = false;
}

rAndroidApplication::~rAndroidApplication(){

}

bool rAndroidApplication::Init(android_app* state){
	m_log = new rAndroidLog();
	rLog::SetLogTarget(m_log);

	rLog::Info("Application Init");

	m_graphicsDevice = new rAndroidGraphicsDevice();
	bool result = m_graphicsDevice->Init(state);

	if (result){
		rLog::Info("Graphics Initialized");

		AAssetManager* assetManager = state->activity->assetManager;
		m_contentManager = new rAndroidContentManager(assetManager, m_graphicsDevice);
		m_contentManager->InitDefaultAssets();

		m_inputManager = new rAndroidInputManager();
		m_renderer = new rRenderer(m_graphicsDevice, m_contentManager);

		TempInit();

		m_engine.input = m_inputManager;
		m_engine.renderer = m_renderer;
		m_engine.content = m_contentManager;
	}
	else{
		rLog::Error("Error initializing graphics");
	}

	return result;
}

void rAndroidApplication::Uninit(){
	m_started = false;
	m_graphicsDevice->Uninit();
}

int32_t rAndroidApplication::OnInput(AInputEvent* event){
	m_inputManager->ProcessInputEvent(event);

	return 1;
}

void rAndroidApplication::ProcessCommand(android_app* app, int32_t cmd){
	switch (cmd){
	case APP_CMD_SAVE_STATE:
		OnSaveStateCommand();
		break;

	case APP_CMD_INIT_WINDOW:
		OnInitWindowCommand(app);
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

void rAndroidApplication::OnInitWindowCommand(android_app* app){
	__android_log_print(ANDROID_LOG_INFO, "recondite", "Application Init Window Command");
	m_started = Init(app);
}

void rAndroidApplication::OnTerminateWindowCommand(){
	rLog::Info("Application Terminate Window Command");
	Uninit();
}

void rAndroidApplication::OnApplicationGainFocusCommand(){
	rLog::Info("Application Gain Focus Command");
}

void rAndroidApplication::OnApplicationLostFocusCommand(){
	rLog::Info("Application Lost Focus Command");
}

void rAndroidApplication::TempInit(){
	m_camera = new rTargetCamera("camera", rVector3(0,0,5));
	m_camera->SetTarget(rVector3(0,0,-5));

	rSize size = m_graphicsDevice->GetSize();

	m_viewport.SetCamera(m_camera);
	m_viewport.SetClipping(1.0, 100.0f);
	m_viewport.SetSize(size.x,size.y);
	m_viewport.SetViewportType(rVIEWPORT_PERSP);
}
