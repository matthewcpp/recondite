#include "reCameraUserController.hpp"

reCameraUserController::reCameraUserController(recondite::Camera* camera, reComponent* component) 
:reCameraController(camera, component){
	_orientation = rVector3::ZeroVector;

	_moveSpeed = 0.5f;
	_wheelSpeed = 5.0;
	_turnSpeed = 3.0;
	_mouseButton = wxMOUSE_BTN_NONE;
	_dragging = false;

	
}

void reCameraUserController::StartDrag(wxMouseEvent& event) {
	_previousPos = event.GetPosition();
	_mouseButton = event.GetButton();
	_dragging = true;
}

void reCameraUserController::EndDrag() {
	_dragging = false;
	_mouseButton = wxMOUSE_BTN_NONE;
}

bool reCameraUserController::OnRightDown(wxMouseEvent& event) {
	StartDrag(event);
	return false;
}

bool reCameraUserController::OnMouseMotion(wxMouseEvent& event) {
	if (!_dragging) {
		return false;
	}
	else {
		if (_mouseButton == wxMOUSE_BTN_RIGHT) 
			DoLook(event);
		else if (_mouseButton == wxMOUSE_BTN_MIDDLE) 
			DoPan(event);

		return true;
	}

	return false;
}
void reCameraUserController::DoPan(wxMouseEvent& event) {
	wxPoint currentPos = event.GetPosition();
	wxPoint delta = currentPos - _previousPos;

	rVector3 cameraPos = _camera->GetPosition();
	rVector3 cameraTarget = _camera->GetTarget();
	rVector3 cameraUp = _camera->GetUp();

	rVector3 cameraForward = _camera->GetTarget() - cameraPos;
	cameraForward.Normalize();

	rVector3 cameraRight = cameraForward.Cross(cameraUp) * _moveSpeed;

	float movement = _moveSpeed;
	if (delta.y > 0) {
		movement *= -1.0f;
	}
	if (delta.y != 0) {
		cameraPos.y += movement;
		cameraTarget.y += movement;
	}

	movement = _moveSpeed;
	if (delta.x < 0) {
		cameraRight *= -1.0f;
	}
	if (delta.x != 0) {
		cameraPos += cameraRight;
		cameraTarget += cameraRight;
	}

	_camera->SetPosition(cameraPos);
	_camera->SetTarget(cameraTarget);

	_previousPos = currentPos;
}


void reCameraUserController::DoLook(wxMouseEvent& event) {
	wxPoint currentPos = event.GetPosition();
	wxPoint delta = currentPos - _previousPos;

	rVector3 cameraUp = _camera->GetUp();
	rVector3 cameraPos = _camera->GetPosition();

	rVector3 cameraForward = _camera->GetTarget() - cameraPos;
	cameraForward.Normalize();

	rVector3 cameraRight = cameraForward.Cross(cameraUp);

	float rot = -_turnSpeed;
	if (delta.x < 0)
		rot *= -1.0f;

	if (delta.x != 0) {
		rQuaternion xform(cameraUp, rot);
		xform.TransformVector3(cameraForward);
	}

	rot = -_turnSpeed;
	if (delta.y < 0)
		rot *= -1.0f;

	if (delta.y != 0) {
		rQuaternion xform(cameraRight, rot);
		xform.TransformVector3(cameraForward);
	}

	_camera->SetTarget(cameraPos + cameraForward);
	_previousPos = currentPos;
}

bool reCameraUserController::OnMousewheel(wxMouseEvent& event) {
	rVector3 cameraPos = _camera->GetPosition();
	rVector3 cameraTarget = _camera->GetTarget();

	rVector3 cameraForward = cameraTarget - cameraPos;
	cameraForward.Normalize();
	cameraForward *= _wheelSpeed;

	if (event.GetWheelRotation() < 0) {
		cameraForward *= -1.0f;
	}

	_camera->SetPosition(cameraPos + cameraForward);
	_camera->SetTarget(cameraTarget + cameraForward);

	return true;
}

bool reCameraUserController::OnMiddleDown(wxMouseEvent& event) {
	StartDrag(event);
	return false;
}

bool reCameraUserController::OnMiddleUp(wxMouseEvent& event) {
	EndDrag();
	return true;
}

bool reCameraUserController::OnRightUp(wxMouseEvent& event) {
	EndDrag();
	return true;
}