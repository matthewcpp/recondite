#ifndef RUI_INTERFACE_HPP
#define RUI_INTERFACE_HPP

#include "rBuild.hpp"

#include "ui/ruiStyleManager.hpp"

class RECONDITE_API ruiIManager {
public:
	virtual ruiStyleManager* Styles() = 0;

	//move this to a InputResponder Interface?
	virtual bool InsertMouseButtonEvent(rMouseButton button, rButtonState state, const rPoint& position) = 0;
	virtual bool InsertMouseWheelEvent(const rPoint& position, rMouseWheelDirection direction) = 0;
	virtual bool InsertMouseMotionEvent(const rPoint& point) = 0;

	virtual bool InsertTouchEvent(int id, const rPoint& position, rTouchType type) = 0;
	virtual bool InsertKeyEvent(rKey key, rKeyState state) = 0;
};

#endif