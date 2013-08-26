#ifndef R_ANDROID_INPUTMANAGER_HPP
#define R_ANDROID_INPUTMANAGER_HPP

#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>

#include "rInputManager.hpp"
#include "rTouch.hpp"


class rAndroidInputManager : rInputManager{
public:

	void ProcessInputEvent(AInputEvent* event);

private:

	void ProcessIndexedTouchEvent(rTouchType type, int actionPointer, AInputEvent* event);
	void ProcessMoveEvent(AInputEvent* event);
	void UpdateTouchEvent(int index, rTouchType type, AInputEvent* event);
};

#endif
