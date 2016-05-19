#include "ui/ruiDefaultEventHandler.hpp"

ruiDefaultEventHandler::ruiDefaultEventHandler(){
	BindDefaultEvents();
}

void ruiDefaultEventHandler::BindDefaultEvents(){
	Bind(ruiEVT_MOUSE_DOWN, this, &ruiDefaultEventHandler::OnMouseDown);
	Bind(ruiEVT_MOUSE_UP, this, &ruiDefaultEventHandler::OnMouseUp);
	Bind(ruiEVT_MOUSE_LEAVE, this, &ruiDefaultEventHandler::OnMouseLeave);
	Bind(ruiEVT_MOUSE_ENTER, this, &ruiDefaultEventHandler::OnMouseEnter);
}

bool ruiDefaultEventHandler::OnPointerDown(const rPoint& position){
	return false;
}

bool ruiDefaultEventHandler::OnPointerUp(const rPoint& position){
	return false;
}

bool ruiDefaultEventHandler::OnPointerLeave(const rPoint& position){
	return false;
}

bool ruiDefaultEventHandler::OnPointerEnter(const rPoint& position){
	return false;
}

void ruiDefaultEventHandler::OnMouseDown(rEvent& event){
	ruiMouseEvent& mouseEvent = static_cast<ruiMouseEvent&>(event);

	if (mouseEvent.Button() == rMOUSE_BUTTON_LEFT)
		event.SetHandled(OnPointerDown(mouseEvent.Position()));
}

void ruiDefaultEventHandler::OnMouseUp(rEvent& event){
	ruiMouseEvent& mouseEvent = static_cast<ruiMouseEvent&>(event);

	if (mouseEvent.Button() == rMOUSE_BUTTON_LEFT)
		event.SetHandled(OnPointerUp(mouseEvent.Position()));
}

void ruiDefaultEventHandler::OnMouseLeave(rEvent& event){
	ruiMouseEvent& mouseEvent = static_cast<ruiMouseEvent&>(event);

	event.SetHandled(OnPointerLeave(mouseEvent.Position()));
}

void ruiDefaultEventHandler::OnMouseEnter(rEvent& event){
	ruiMouseEvent& mouseEvent = static_cast<ruiMouseEvent&>(event);
	event.SetHandled(OnPointerEnter(mouseEvent.Position()));
}