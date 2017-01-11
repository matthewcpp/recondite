#pragma once

#include "reCameraController.hpp"

class reCameraOrientationController : public reCameraController {
public:
	reCameraOrientationController(reViewOrientation orientation, recondite::Camera* camera, reComponent* component);

	virtual bool OnRightDown(wxMouseEvent& event);
	virtual bool OnMouseMotion(wxMouseEvent& event);
	virtual bool OnRightUp(wxMouseEvent& event);

	virtual bool OnMousewheel(wxMouseEvent& event) override;

private:
	rVector2 GetMovementValues(const wxPoint& delta);

private:
	reViewOrientation _orientation;

	bool _dragging;
	wxPoint _previousPos;
	int _activeButton;
	float _moveSpeed;
};