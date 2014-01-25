#ifndef R_ANDROIDAPPLICATION_HPP
#define R_ANDROIDAPPLICATION_HPP

#include <time.h>

#include "rDefs.hpp"
#include "rTypes.hpp"

#include "rAndroidInputManager.hpp"
#include "rAndroidContentManager.hpp"
#include "rAndroidLog.hpp"
#include "rAndroidGraphicsDevice.hpp"

#include "rApplication.hpp"

#include "rLog.hpp"
#include "rModule.hpp"

class rAndroidApplication : public rApplication{
public:
	rAndroidApplication(rModule* module);
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

	virtual void Update();
	virtual void Draw();

	virtual unsigned long GetTimeMiliseconds() const;


protected:

	rAndroidLog* m_log;
	rAndroidContentManager* m_contentManager;
	rAndroidInputManager* m_inputManager;
	rAndroidGraphicsDevice* m_graphicsDevice;

	bool m_started;
};

#endif
