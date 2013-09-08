#include "rAndroidInputManager.hpp"

//http://mobilepearls.com/labs/native-android-api/include/android/input.h
//https://groups.google.com/forum/#!topic/android-ndk/EYMmEY89pJo

void rAndroidInputManager::ProcessIndexedTouchEvent(rTouchType type, int actionPointer, AInputEvent* event){
	int index = (actionPointer & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK)  >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;

	UpdateTouchEvent(index, type, event);
}

void rAndroidInputManager::UpdateTouchEvent(int index, rTouchType type, AInputEvent* event){
	int pointerId = AMotionEvent_getPointerId(event, index);
	rPoint position((int)AMotionEvent_getX(event, index), (int)AMotionEvent_getY(event, index));

	if (type == rTOUCH_DOWN){
		CreateTouch(pointerId, position);
	}
	else {
		UpdateTouch(pointerId, position, type);
	}
}

void rAndroidInputManager::ProcessMoveEvent(AInputEvent* event){
	int pointerCount = AMotionEvent_getPointerCount(event);

	for (int index = 0; index < pointerCount; index++){
		UpdateTouchEvent(index, rTOUCH_MOVE, event);
	}
}

void rAndroidInputManager::ProcessInputEvent(AInputEvent* event){
	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {

		int actionPointer = AKeyEvent_getAction(event);
		int flags = actionPointer & AMOTION_EVENT_ACTION_MASK;

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
	else if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_KEY){

	}
}
