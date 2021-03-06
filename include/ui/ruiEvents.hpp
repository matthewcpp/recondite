#ifndef RUI_EVENTS_HPP
#define RUI_EVENTS_HPP

#include "rEvent.hpp"
#include "rEventHandler.hpp"

#include "input/rMouse.hpp"
#include "ui/ruiMenu.hpp"
#include "input/rKeyboard.hpp"

class ruiWidget;

enum ruiEventType{
	ruiEVT_MOUSE_DOWN,
	ruiEVT_MOUSE_UP,
	ruiEVT_MOUSE_MOTION,
	ruiEVT_MOUSE_WHEEL,
	ruiEVT_MOUSE_ENTER,
	ruiEVT_MOUSE_LEAVE,

	ruiEVT_KEY_DOWN,
	ruiEVT_KEY_UP,

	ruiEVT_TOUCH_DOWN,
	ruiEVT_TOUCH_MOVE,
	ruiEVT_TOUCH_UP,

	ruiEVT_MENU,

	ruiEVENT_BUTTON_CLICK,
	ruiEVENT_CHECKBOX_CHANGE,
	ruiEVENT_SLIDER_CHANGE,
	ruiEVENT_SLIDER_DRAG_BEGIN,
	ruiEVENT_SLIDER_DRAG_MOVE,
	ruiEVENT_SLIDER_DRAG_END,
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

class ruiWidgetEvent : public rEvent{
public:
	ruiWidgetEvent(ruiWidget* widget) : m_widget(widget){}
	ruiWidget* Widget() const { return m_widget; }
private:
	ruiWidget* m_widget;
};

class ruiMenuEvent : public rEvent{
public:
	ruiMenuEvent(ruiMenu* menu, int selection): m_menu(menu), m_selection(selection) {}

	ruiMenu* Menu() const {return m_menu;}
	int Selection() const {return m_selection;}

private:
	ruiMenu* m_menu;
	int m_selection;
};

class ruiKeyEvent : public rEvent{
public:
	ruiKeyEvent(rKey key, rKeyState state) : _key(key), _state(state){}

	rKey Key() const { return _key; }
	rKeyState State() const { return _state; }

private:
	rKey _key;
	rKeyState _state;
};

#endif