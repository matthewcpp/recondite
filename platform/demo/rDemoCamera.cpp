#include "rDemoCamera.hpp"

rDemoCamera::rDemoCamera(const rString& name , const rVector3& position)
	:rOrbitCamera(name, position)
{
	m_orbitSpeed = 180.0f;
	m_orbiting = false;

	m_lastWheelValue = INT_MIN;
	m_pinchAmount = 0.0f;
}

float rDemoCamera::OrbitSpeed() const{
	return m_orbitSpeed;
}

void rDemoCamera::SetOrbitSpeed(float speed){
	m_orbitSpeed = speed;

	if (m_orbitSpeed < 1.0f)
		m_orbitSpeed = 1.0f;
}

int rDemoCamera::CalculateZoomDirection(int wheelValue){
	int ret = 0;
	if (m_lastWheelValue != INT_MIN){
		if (wheelValue > m_lastWheelValue)
			ret = 1;
		else if (wheelValue < m_lastWheelValue)
			ret = -1;
	}

	m_lastWheelValue = wheelValue;
	return ret;
}

bool rDemoCamera::ProcessMouse(rEngine& engine){
	const rMouseState* state = engine.input->GetMouseState();

	DoZoom(CalculateZoomDirection(state->GetWheelValue()));

	if (state->GetButtonState(rMOUSE_BUTTON_LEFT) == rBUTTON_STATE_DOWN){
		if (m_orbiting){
			DoOrbit(state->Position(), engine.time.TimeDeltaSeconds());
		}
		else {
			m_lastUpdatePos = state->Position();
			m_orbiting = true;
		}

		return true;
	}
	else {
		m_orbiting = false;
		return false;
	}
}

bool rDemoCamera::ProcessTouch(rEngine& engine){
	float amount = engine.input->Gestures()->AmountDelta("pinch");

	if (amount != m_pinchAmount){
		DoZoom( amount * 100.0f);
	}
	else if (engine.input->Gestures()->Active("drag")){
		DoOrbit(engine.input->Gestures()->Position("drag", 0), engine.time.TimeDeltaSeconds());
	}

	m_pinchAmount = amount;
}

int rDemoCamera::Update(rEngine& engine){

	bool processed = ProcessMouse(engine);

	if (!processed)
		ProcessTouch(engine);

	rOrbitCamera::Update(engine);

	return 0;
}

void rDemoCamera::DoZoom(int zoomDirection){

	if (zoomDirection > 0)
		MoveCloserIn();
	else if (zoomDirection < 0)
		MoveFartherAway();
}

void rDemoCamera::DoOrbit (const rPoint& position, float timeDelta){
	float amount = m_orbitSpeed * timeDelta;

	rPoint delta = position - m_lastUpdatePos;

	if (delta.x > 0)
		SetYaw(Yaw() -amount);
	else if (delta.x < 0)
		SetYaw(Yaw() + amount);

	if (delta.y > 0)
		SetRoll(Roll() + amount);
	else if (delta.y < 0)
		SetRoll(Roll() - amount);

	m_lastUpdatePos = position;
}
