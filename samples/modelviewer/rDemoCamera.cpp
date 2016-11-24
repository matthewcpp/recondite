#include "rDemoCamera.hpp"

rDemoCamera::rDemoCamera(recondite::Camera* camera, const rString& name , rEngine* engine)
	:rActor3(name, engine)
{
	m_camera = camera;
	m_orbitSpeed = 180.0f;
	m_panSpeed = 10.0;
	m_dragging = false;

	m_cameraAngle = rVector3::ZeroVector;

	m_lastWheelValue = INT_MIN;
	m_pinchAmount = 0.0f;

	Reset(rVector3::ZeroVector, 1.0f, 0.0f, 0.0f);
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

	if (m_needsUpdate)
		UpdatePosition();

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

void rDemoCamera::Reset(const rVector3 target, float radius, float yaw, float roll) {
	m_camera->SetTarget(target);
	m_radius = radius;
	m_distance = radius;
	m_cameraAngle.y = yaw;
	m_cameraAngle.x = roll;

	UpdatePosition();
}

void rDemoCamera::UpdatePosition() {
	rQuaternion xform(m_cameraAngle);
	rVector3 cameraVector = rVector3::BackwardVector;
	xform.TransformVector3(cameraVector);
	rQuaternion::ToEuler(xform, m_rotation);

	cameraVector *= m_distance;
	m_camera->SetPosition(m_camera->GetTarget() + cameraVector);

	m_needsUpdate = false;
}

void rDemoCamera::SetYaw(float yaw) {
	m_cameraAngle.y = yaw;
	m_needsUpdate = true;
}

float rDemoCamera::Yaw() const {
	return m_cameraAngle.y;
}

void rDemoCamera::SetRoll(float roll) {
	m_cameraAngle.x = roll;
	m_needsUpdate = true;
}

float rDemoCamera::Roll() const {
	return m_cameraAngle.x;
}

float rDemoCamera::Radius() const {
	return m_radius;
}

void rDemoCamera::SetRadius(float radius) {
	m_radius = radius;
	m_needsUpdate = true;
}

float rDemoCamera::Distance() const {
	return m_distance;
}

void rDemoCamera::SetDistance(float distance) {
	m_distance = distance;

	float minDistance = m_radius / 10.0f;
	if (m_distance < minDistance)
		m_distance = minDistance;

	m_needsUpdate = true;
}

void rDemoCamera::MoveCloserIn() {
	float step = m_radius / 10.0f;
	SetDistance(m_distance - step);
}

void rDemoCamera::MoveFartherAway() {
	float step = m_radius / 10.0f;
	SetDistance(m_distance + step);
}

void rDemoCamera::SetTarget(const rVector3& target) {
	m_camera->SetTarget(target);
	m_needsUpdate = true;
}

rVector3 rDemoCamera::Target() const {
	return m_camera->GetTarget();
}

rString rDemoCamera::ClassName() const {
	return "Temp";
}