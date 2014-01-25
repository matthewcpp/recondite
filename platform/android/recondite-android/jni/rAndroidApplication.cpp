#include "rAndroidApplication.hpp"

rAndroidApplication::rAndroidApplication(rModule* module)
:rApplication(module)
{
	m_log = NULL;
	m_contentManager = NULL;
	m_inputManager = NULL;
	m_graphicsDevice = NULL;

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
		m_inputManager = new rAndroidInputManager();

		InitEngine(m_graphicsDevice, m_contentManager, m_inputManager);
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

void rAndroidApplication::Update(){
	if (m_started){
		rApplication::Update();
	}
}

void rAndroidApplication::Draw(){
	if (m_started){
		rApplication::Draw();
	}
}

unsigned long rAndroidApplication::GetTimeMiliseconds() const{
	struct timespec res;
	clock_gettime(CLOCK_REALTIME, &res);

	return 1000 * res.tv_sec +  (res.tv_nsec / 1000000);
}
