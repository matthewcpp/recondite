#include "rwxViewCameraInteraction.hpp"

rwxViewCameraInteraction::rwxViewCameraInteraction(rCamera* camera){
	m_camera = camera;
}

bool rwxViewCameraInteraction::UpdateKeyboardInteraction(){
	bool updated = false;

	if (wxGetKeyState((wxKeyCode)'w') || wxGetKeyState(WXK_UP)){
		m_camera->MoveForward(0.50f);
		updated = true;
	}
	else if (wxGetKeyState((wxKeyCode)'s') || wxGetKeyState(WXK_DOWN)){
		m_camera->MoveBackward(0.50f);
		updated = true;
	}

	if (wxGetKeyState((wxKeyCode)'a') || wxGetKeyState(WXK_LEFT)){
		m_camera->MoveLeft(0.50f);
		updated = true;
	}
	else if (wxGetKeyState((wxKeyCode)'d') || wxGetKeyState(WXK_RIGHT)){
		m_camera->MoveRight(0.50f);
		updated = true;
	}

	return updated;
}