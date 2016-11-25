#pragma once

#include "rCamera.hpp"

#include "project/reComponent.hpp"

class reCameraController {
public:
	reCameraController(recondite::Camera* camera, reComponent* component) : _camera(camera), _component(component) {}

	virtual bool OnMouseMotion(wxMouseEvent& event) { return false; }
	virtual bool OnMiddleDown(wxMouseEvent& event) { return false; }
	virtual bool OnMiddleUp(wxMouseEvent& event) { return false; }
	virtual bool OnRightDown(wxMouseEvent& event) { return false; }
	virtual bool OnRightUp(wxMouseEvent& event) { return false; }
	virtual bool OnMousewheel(wxMouseEvent& event) { return false; }

	virtual bool UpdateKeyboardInteraction() { return false; }

protected:
	reComponent* _component;
	recondite::Camera* _camera;
};