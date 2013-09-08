#ifndef R_ANDROIDAPPLICATION_HPP
#define R_ANDROIDAPPLICATION_HPP

#include "rDefs.hpp"
#include "rTypes.hpp"

#include "rAndroidInputManager.hpp"
#include "rAndroidContentManager.hpp"
#include "rAndroidLog.hpp"
#include "rAndroidGraphicsDevice.hpp"

#include "rLog.hpp"
#include "rRenderer.hpp"

#include "rGameTime.hpp"
#include "rLog.hpp"

class rAndroidApplication{
public:
	rAndroidApplication();
	virtual ~rAndroidApplication();

	bool Init(android_app* state);
	void Uninit();

	int32_t OnInput(AInputEvent* event);

	void ProcessCommand(android_app* app, int32_t cmd);

	void OnSaveStateCommand();
	void OnInitWindowCommand(android_app* app);
	void OnTerminateWindowCommand();
	void OnApplicationGainFocusCommand();
	void OnApplicationLostFocusCommand();

	void Draw();

	void TempInit();

public:

	rAndroidLog* m_log;
	rAndroidContentManager* m_contentManager;
	rAndroidInputManager* m_inputManager;
	rAndroidGraphicsDevice* m_graphicsDevice;

	rRenderer* m_renderer;
	rViewport m_viewport;
	rTargetCamera* m_camera;
	rGameTime m_gameTime;
};

#endif
