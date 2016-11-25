#pragma once

#include "reCameraController.hpp"

class reCameraUserController : public reCameraController {
public:
	reCameraUserController(recondite::Camera* camera, reComponent* component);

	virtual bool OnRightDown(wxMouseEvent& event);
	virtual bool OnMouseMotion(wxMouseEvent& event);
	virtual bool OnRightUp(wxMouseEvent& event);

	virtual bool OnMiddleDown(wxMouseEvent& event);
	virtual bool OnMiddleUp(wxMouseEvent& event);

	virtual bool OnMousewheel(wxMouseEvent& event);

private:
	void StartDrag(wxMouseEvent& event);
	void EndDrag();

	void DoLook(wxMouseEvent& event);
	void DoPan(wxMouseEvent& event);

private:
	float _moveSpeed;
	float _wheelSpeed;
	float _turnSpeed;
	float _dragging;

	wxPoint _previousPos;
	int _mouseButton;

	rVector3 _orientation;
};