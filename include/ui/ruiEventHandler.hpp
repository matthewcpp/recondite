#ifndef RUI_EVENTHANDLER_HPP
#define RUI_EVENTHANDLER_HPP

#include "input/rMouse.hpp"
#include "input/rTouch.hpp"

class ruiEventHandler{
public:
	virtual void OnTouchDown(const rTouch& touch) {}
	virtual void OnTouchMove(const rTouch& touch) {}
	virtual void OnTouchUp(const rTouch& touch) {}

	virtual void OnMouseLeftDown(const rMouseState& mouse) {}
	virtual void OnMouseLeftUp(const rMouseState& mouse) {}
	virtual void OnMouseMiddleDown(const rMouseState& mouse) {}
	virtual void OnMouseMiddleUp(const rMouseState& mouse) {}
	virtual void OnMouseRightDown(const rMouseState& mouse) {}
	virtual void OnMouseRightUp(const rMouseState& mouse) {}
	virtual void OnMouseMotion(const rMouseState& mouse){}
	virtual void OnMouseWheelUp(const rMouseState& mouse){}
	virtual void OnMouseWheelDown(const rMouseState& mouse){}

	virtual void OnPointerDown(const rPoint& position) {}
	virtual void OnPointerUp(const rPoint& position) {}
	virtual void OnPointerMove(const rPoint& position) {}

	void MouseDownEvent(rMouseButton button, const rMouseState& mouse);
	void MouseUpEvent(rMouseButton button, const rMouseState& mouse);
	void MouseWheelEvent(rMouseWheelDirection direction, const rMouseState& mouse);
};

#endif