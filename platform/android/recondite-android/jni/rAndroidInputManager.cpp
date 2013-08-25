#include "rAndroidInputManager.hpp"

//http://mobilepearls.com/labs/native-android-api/include/android/input.h
//https://groups.google.com/forum/#!topic/android-ndk/EYMmEY89pJo

void rAndroidInputManager::ProcessIndexedTouchEvent(rTouchType type, int actionPointer, AInputEvent* event){
	int index = (actionPointer & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK)  >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;

	UpdateTouchEvent(index, type, event);
}

void rAndroidInputManager::UpdateTouchEvent(int index, rTouchType type, AInputEvent* event){
	int pointerId = AMotionEvent_getPointerId(event, index);
	int posX = (int)AMotionEvent_getX(event, index);
	int posY = (int)AMotionEvent_getY(event, index);
}

void rAndroidInputManager::ProcessMoveEvent(AInputEvent* event){
	int pointerCount = AMotionEvent_getPointerCount(event);

	for (int index = 0; index < pointerCount; index++){
		UpdateTouchEvent(index, rTouchMove, event);
	}
}

void rAndroidInputManager::ProcessInputEvent(AInputEvent* event){
	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {

		int action = AKeyEvent_getAction(event);
		int flags = action & AMOTION_EVENT_ACTION_MASK;

		switch (flags){
			case AMOTION_EVENT_ACTION_POINTER_UP:
			case AMOTION_EVENT_ACTION_UP:
				ProcessIndexedTouchEvent(rTOUCH_UP, actionPointer, event);
			break;

			case AMOTION_EVENT_ACTION_POINTER_DOWN:
			case AMOTION_EVENT_ACTION_DOWN:
				ProcessIndexedTouchEvent(rTOUCH_DOWN, actionPointer, event);
			break;

			case AMOTION_EVENT_ACTION_MOVE:
				ProcessMoveEvent(event);
			break;
		};
	}
}
