#include "rDemoCamera.hpp"

rDemoCamera::rDemoCamera(const rString& name , rEngine* engine)
	:rOrbitCamera(name, engine)
{
	m_orbitSpeed = 180.0f;
	m_panSpeed = 10.0;
	m_dragging = false;

	m_lastWheelValue = INT_MIN;
	m_pinchAmount = 0.0f;
}

float rDemoCamera::OrbitSpeed() const{
	return m_orbitSpeed;
}

void rDemoCamera::SetOrbitSpeed(float speed){
	m_orbitSpeed = speed;
}

void rDemoCamera::SetPanSpeed(float speed) {
	m_panSpeed = speed;
}

float rDemoCamera::PanSpeed() const {
	return m_panSpeed;
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

bool rDemoCamera::ProcessMouse(){
	const rMouseState* state = m_engine->input->GetMouseState();

	DoZoom(CalculateZoomDirection(state->GetWheelValue()));

	if (state->GetButtonState(rMOUSE_BUTTON_LEFT) == rBUTTON_STATE_DOWN){
		if (m_dragging){
			DoOrbit(state->Position(), m_engine->time.TimeDeltaSeconds());
		}
		else {
			m_lastUpdatePos = state->Position();
			m_dragging = true;
		}

		return true;
	}
	else if (state->GetButtonState(rMOUSE_BUTTON_RIGHT) == rBUTTON_STATE_DOWN) {
		if (m_dragging) {
			DoPan(state->Position(), m_engine->time.TimeDeltaSeconds());
		}
		else {
			m_lastUpdatePos = state->Position();
			m_dragging = true;
		}
	}
	else {
		m_dragging = false;
		return false;
	}
}

bool rDemoCamera::ProcessTouch(){
	float amount = m_engine->input->Gestures()->AmountDelta("pinch");

	if (amount != m_pinchAmount){
		DoZoom( amount * 100.0f);
		return true;
	}
	else if (m_engine->input->Gestures()->Active("drag")){
		DoOrbit(m_engine->input->Gestures()->Position("drag", 0), m_engine->time.TimeDeltaSeconds());
		return true;
	}

	m_pinchAmount = amount;
	return false;
}

int rDemoCamera::Update(){

	bool processed = ProcessMouse();

	if (!processed)
		ProcessTouch();

	rOrbitCamera::Update();

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

void rDemoCamera::DoPan(const rPoint& position, float timeDelta) {
	float amount = m_panSpeed * timeDelta;
	rPoint positionDelta = position - m_lastUpdatePos;

	rVector3 right = Right();
	right *= positionDelta.x * amount;

	rVector3 up = Up();
	up *= positionDelta.y * amount;

	rVector3 cameraDelta = right + up;

	SetPosition(Position() + cameraDelta);
	SetTarget(Target() + cameraDelta);

	m_lastUpdatePos = position;
}
