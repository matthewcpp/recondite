#include "ui/ruiEventHandler.hpp"

void ruiEventHandler::MouseDownEvent(rMouseButton button, const rMouseState& mouse){
	switch (button){
	case rMOUSE_BUTTON_LEFT:
		OnMouseLeftDown(mouse);
		break;

	case rMOUSE_BUTTON_MIDDLE:
		OnMouseMiddleDown(mouse);
		break;

	case rMOUSE_BUTTON_RIGHT:
		OnMouseRightDown(mouse);
		break;
	};
}

void ruiEventHandler::MouseUpEvent(rMouseButton button, const rMouseState& mouse){
		switch (button){
	case rMOUSE_BUTTON_LEFT:
		OnMouseLeftUp(mouse);
		break;

	case rMOUSE_BUTTON_MIDDLE:
		OnMouseMiddleUp(mouse);
		break;

	case rMOUSE_BUTTON_RIGHT:
		OnMouseRightUp(mouse);
		break;
	};
}

void ruiEventHandler::MouseWheelEvent(rMouseWheelDirection direction, const rMouseState& mouse){
	if (direction == rMOUSEWHEEL_UP)
		OnMouseWheelUp(mouse);
	else
		OnMouseWheelDown(mouse);
}