#include "controllers/reCameraOrientationController.hpp"

reCameraOrientationController::reCameraOrientationController(reViewOrientation orientation, recondite::Camera* camera, reComponent* component)
	:reCameraController(camera, component)
{
	_orientation = orientation;
	_dragging = false;
	_moveSpeed = 0.5f;
}

bool reCameraOrientationController::OnRightDown(wxMouseEvent& event) {
	_previousPos = event.GetPosition();
	_dragging = true;
	_activeButton = event.GetButton();

	return true;
}

bool reCameraOrientationController::OnMouseMotion(wxMouseEvent& event) {
	if (_dragging) {
		wxPoint currentPos = event.GetPosition();
		wxPoint delta = currentPos - _previousPos;

		rVector2 move = GetMovementValues(delta);

		rVector3 position = _camera->GetPosition();
		rVector3 target = _camera->GetTarget();

		switch (_orientation) {
			case reViewOrientation::Top:
				position.x += move.y;
				position.z += -move.x;
				target.x += move.y;
				target.z += -move.x;
				break;

			case reViewOrientation::Bottom:
				position.x += move.y;
				position.z += move.x;
				target.x += move.y;
				target.z += move.x;
				break;

			case reViewOrientation::Right:
				position.y += move.y;
				position.z += move.x;
				target.y += move.y;
				target.z += move.x;
				break;

			case reViewOrientation::Left:
				position.y += move.y;
				position.z += -move.x;
				target.y += move.y;
				target.z += -move.x;
				break;

			case reViewOrientation::Front:
				position.y += move.y;
				position.x +=-move.x;
				target.y += move.y;
				target.x += -move.x;
				break;

			case reViewOrientation::Back:
				position.y += move.y;
				position.x += move.x;
				target.y += move.y;
				target.x += move.x;
				break;
		};

		_camera->SetPosition(position);
		_camera->SetTarget(target);

		_previousPos = currentPos;

		return true;
	}

	return false;
}

bool reCameraOrientationController::OnRightUp(wxMouseEvent& event) {
	_dragging = false;

	return true;
}

rVector2 reCameraOrientationController::GetMovementValues(const wxPoint& delta) {
	rVector2 move = rVector2::ZeroVector;

	if (delta.x > 0) move.x = _moveSpeed;
	else if (delta.x < 0) move.x = -_moveSpeed;

	if (delta.y > 0) move.y = _moveSpeed;
	else if (delta.y < 0) move.y = -_moveSpeed;

	return move;
}