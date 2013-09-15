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

#include "rEngine.hpp"
#include "rLog.hpp"

class rAndroidApplication{
public:
	rAndroidApplication();
	virtual ~rAndroidApplication();

	virtual bool Init(android_app* state);
	void Uninit();

	int32_t OnInput(AInputEvent* event);

	void ProcessCommand(android_app* app, int32_t cmd);

	void OnSaveStateCommand();
	void OnInitWindowCommand(android_app* app);
	void OnTerminateWindowCommand();
	void OnApplicationGainFocusCommand();
	void OnApplicationLostFocusCommand();

	virtual void Update() = 0;
	virtual void Draw() = 0;

	void TempInit();

protected:

	rAndroidLog* m_log;
	rAndroidContentManager* m_contentManager;
	rAndroidInputManager* m_inputManager;
	rAndroidGraphicsDevice* m_graphicsDevice;

	rRenderer* m_renderer;
	rViewport m_viewport;
	rTargetCamera* m_camera;

	rEngine m_engine;

	bool m_started;
};

#endif
