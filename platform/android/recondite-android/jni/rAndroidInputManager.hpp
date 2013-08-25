#ifndef R_ANDROID_INPUTMANAGER_HPP
#define R_ANDROID_INPUTMANAGER_HPP

#include <android/sensor.h>

#include "rAndroidLog.hpp"
#include "rTouch.hpp"

class rAndroidInputManager{
public:

	void ProcessInputEvent(AInputEvent* event);

private:

	void ProcessIndexedTouchEvent(rTouchType type, int actionPointer, AInputEvent* event);
	void ProcessMoveEvent(AInputEvent* event);
	void UpdateTouchEvent(int index, rTouchType type, AInputEvent* event);
};

#endif
