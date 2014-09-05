#ifndef RUI_EVENTS_HPP
#define RUI_EVENTS_HPP

#include "rEvent.hpp"
#include "input/rMouse.hpp"

enum ruiEventType{
	ruiEVT_MOUSE_DOWN,
	ruiEVT_MOUSE_UP,
	ruiEVT_MOUSE_MOTION,
	ruiEVT_MOUSE_WHEEL,
	ruiEVT_MOUSE_ENTER,
	ruiEVT_MOUSE_LEAVE,

	ruiEVT_TOUCH_DOWN,
	ruiEVT_TOUCH_MOVE,
	ruiEVT_TOUCH_UP,

	//temp
	ruiEVENT_BUTTON_CLICK,
	ruiEVENT_CHECKBOX_CHANGE,
	ruiEVENT_SLIDER_CHANGE,
	ruiEVENT_PICKER_CHANGE
};

class ruiMouseEvent : public rEvent{
public:
	ruiMouseEvent(const rPoint& position) : m_button(rMOUSE_BUTTON_NONE), m_buttonState(rBUTTON_STATE_NONE), m_position(position), m_wheelDirection(rMOUSEWHEEL_NONE){}
	ruiMouseEvent(rMouseButton button, rButtonState buttonState, const rPoint& position) : m_button(button), m_buttonState(buttonState), m_position(position), m_wheelDirection(rMOUSEWHEEL_NONE) {}
	ruiMouseEvent(rMouseWheelDirection wheelDirection, const rPoint& position) : m_button(rMOUSE_BUTTON_NONE), m_buttonState(rBUTTON_STATE_NONE), m_position(position), m_wheelDirection(wheelDirection){}

	rMouseButton Button() const {return m_button;}
	rMouseWheelDirection WheelDirection() const {return m_wheelDirection;}
	rPoint Position () const {return m_position;}

private:
	rMouseButton m_button;
	rPoint m_position;
	rMouseWheelDirection m_wheelDirection;
	rButtonState m_buttonState;
};

#endif