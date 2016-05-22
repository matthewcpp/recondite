#include "ui/ruiDefaultEventHandler.hpp"

ruiDefaultEventHandler::ruiDefaultEventHandler(){
	dragging = false;
	BindDefaultEvents();
}

void ruiDefaultEventHandler::BindDefaultEvents(){
	Bind(ruiEVT_MOUSE_DOWN, this, &ruiDefaultEventHandler::OnMouseDown);
	Bind(ruiEVT_MOUSE_UP, this, &ruiDefaultEventHandler::OnMouseUp);
	Bind(ruiEVT_MOUSE_MOTION, this, &ruiDefaultEventHandler::OnMouseMotion);
	Bind(ruiEVT_MOUSE_LEAVE, this, &ruiDefaultEventHandler::OnMouseLeave);
	Bind(ruiEVT_MOUSE_ENTER, this, &ruiDefaultEventHandler::OnMouseEnter);
}

bool ruiDefaultEventHandler::OnPointerDown(const rPoint& position){
	return false;
}

bool ruiDefaultEventHandler::OnPointerUp(const rPoint& position){
	return false;
}

bool ruiDefaultEventHandler::OnPointerMove(const rPoint& position){
	return false;
}

bool ruiDefaultEventHandler::OnPointerLeave(const rPoint& position){
	return false;
}

bool ruiDefaultEventHandler::OnPointerEnter(const rPoint& position){
	return false;
}

void ruiDefaultEventHandler::OnMouseDown(rEvent& event){
	ruiMouseEvent& mouseEvent = (ruiMouseEvent&)(event);

	if (mouseEvent.Button() == rMOUSE_BUTTON_LEFT){
		event.SetHandled(OnPointerDown(mouseEvent.Position()));
		dragging = true;
	}
		
}

void ruiDefaultEventHandler::OnMouseUp(rEvent& event){
	ruiMouseEvent& mouseEvent = (ruiMouseEvent&)(event);

	if (mouseEvent.Button() == rMOUSE_BUTTON_LEFT){
		event.SetHandled(OnPointerUp(mouseEvent.Position()));
		dragging = false;
	}
		
}

void ruiDefaultEventHandler::OnMouseMotion(rEvent& event){
	ruiMouseEvent& mouseEvent = (ruiMouseEvent&)(event);

	if (dragging){
		event.SetHandled(OnPointerMove(mouseEvent.Position()));
	}
}

void ruiDefaultEventHandler::OnMouseLeave(rEvent& event){
	ruiMouseEvent& mouseEvent = (ruiMouseEvent&)(event);

	event.SetHandled(OnPointerLeave(mouseEvent.Position()));
}

void ruiDefaultEventHandler::OnMouseEnter(rEvent& event){
	ruiMouseEvent& mouseEvent = (ruiMouseEvent&)(event);
	event.SetHandled(OnPointerEnter(mouseEvent.Position()));
}