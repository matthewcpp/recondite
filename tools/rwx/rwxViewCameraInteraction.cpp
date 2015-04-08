#include "rwxViewCameraInteraction.hpp"

rwxViewCameraInteraction::rwxViewCameraInteraction(rCamera* camera){
	m_camera = camera;
	m_activeButton = rMOUSE_BUTTON_NONE;
	m_cameraRotation = rVector3::ZeroVector;

	m_cameraRotateSpeed = 2.0f;
	m_cameraMoveSpeed = 0.5f;

	m_targetDistance = 10.0f;
}

bool rwxViewCameraInteraction::UpdateKeyboardInteraction(){
	bool updated = false;

	if (wxGetKeyState((wxKeyCode)'w') || wxGetKeyState(WXK_UP)){
		m_camera->MoveForward(m_cameraMoveSpeed);
		updated = true;
	}
	else if (wxGetKeyState((wxKeyCode)'s') || wxGetKeyState(WXK_DOWN)){
		m_camera->MoveBackward(m_cameraMoveSpeed);
		updated = true;
	}

	if (wxGetKeyState((wxKeyCode)'a') || wxGetKeyState(WXK_LEFT)){
		m_camera->MoveLeft(m_cameraMoveSpeed);
		updated = true;
	}
	else if (wxGetKeyState((wxKeyCode)'d') || wxGetKeyState(WXK_RIGHT)){
		m_camera->MoveRight(m_cameraMoveSpeed);
		updated = true;
	}

	if (updated)
		SetCameraTarget();

	return updated;
}

bool rwxViewCameraInteraction::OnMouseMotion(wxMouseEvent& event){
	wxPoint pt = event.GetPosition();
	wxPoint delta = m_previousPt - pt;
	bool refresh = false;

	if (m_activeButton == rMOUSE_BUTTON_MIDDLE){
		if (delta.y > 0){
			m_camera->MoveUp(m_cameraMoveSpeed);
			refresh = true;
		}
		else if (delta.y < 0){
			m_camera->MoveDown(m_cameraMoveSpeed);
			refresh = true;
		}
	}
	else if (m_activeButton == rMOUSE_BUTTON_RIGHT){
		if (delta.x > 0){
			m_cameraRotation.y += m_cameraRotateSpeed;
			refresh = true;
		}
		else if (delta.x < 0){
			m_cameraRotation.y -= m_cameraRotateSpeed;
			refresh = true;
		}

		if (delta.y > 0){
			m_cameraRotation.x += m_cameraRotateSpeed;
			refresh = true;
		}
		else if (delta.y < 0){
			m_cameraRotation.x -= m_cameraRotateSpeed;
			refresh = true;
		}
	}

	if (refresh)
		SetCameraTarget();

	m_previousPt = pt;

	return refresh;
}

bool rwxViewCameraInteraction::OnMiddleDown(wxMouseEvent& event){
	m_previousPt = event.GetPosition();
	m_activeButton = rMOUSE_BUTTON_MIDDLE;

	return false;
}

bool rwxViewCameraInteraction::OnMiddleUp(wxMouseEvent& event){
	m_activeButton = rMOUSE_BUTTON_NONE;

	return false;
}

bool rwxViewCameraInteraction::OnRightDown(wxMouseEvent& event){
	m_previousPt = event.GetPosition();
	m_activeButton = rMOUSE_BUTTON_RIGHT;
	return false;
}

bool rwxViewCameraInteraction::OnRightUp(wxMouseEvent& event){
	m_activeButton = rMOUSE_BUTTON_NONE;

	return false;
}

bool rwxViewCameraInteraction::OnMousewheel(wxMouseEvent& event){


	return false;
}

void rwxViewCameraInteraction::SetCameraTarget(){
	rQuaternion q(m_cameraRotation);
	rVector3 targetDirection = rVector3::ForwardVector;
	q.TransformVector3(targetDirection);
	rVector3 targetPosition = m_camera->Position() + (targetDirection * m_targetDistance);
	m_camera->SetTarget(targetPosition);
}