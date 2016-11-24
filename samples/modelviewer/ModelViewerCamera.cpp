#include "ModelViewerCamera.hpp"

ModelViewerCamera::ModelViewerCamera(recondite::Camera* camera, const rString& name , rEngine* engine)
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

float ModelViewerCamera::OrbitSpeed() const{
	return m_orbitSpeed;
}

void ModelViewerCamera::SetOrbitSpeed(float speed){
	m_orbitSpeed = speed;
}

void ModelViewerCamera::SetPanSpeed(float speed) {
	m_panSpeed = speed;
}

float ModelViewerCamera::PanSpeed() const {
	return m_panSpeed;
}

int ModelViewerCamera::CalculateZoomDirection(int wheelValue){
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

bool ModelViewerCamera::ProcessMouse(){
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

		return true;
	}
	else {
		m_dragging = false;
		return false;
	}
}

bool ModelViewerCamera::ProcessTouch(){
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

int ModelViewerCamera::Update(){

	bool processed = ProcessMouse();

	if (!processed)
		ProcessTouch();

	if (m_needsUpdate)
		UpdatePosition();

	return 0;
}

void ModelViewerCamera::DoZoom(int zoomDirection){

	if (zoomDirection > 0)
		MoveCloserIn();
	else if (zoomDirection < 0)
		MoveFartherAway();
}

void ModelViewerCamera::DoOrbit (const rPoint& position, float timeDelta){
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

void ModelViewerCamera::DoPan(const rPoint& position, float timeDelta) {
	rQuaternion xform(m_cameraAngle);

	float amount = m_panSpeed * timeDelta;
	rPoint positionDelta = position - m_lastUpdatePos;

	rVector3 right = rVector3::RightVector;
	xform.TransformVector3(right);

	right *= positionDelta.x * amount;

	rVector3 up = rVector3::UpVector;
	xform.TransformVector3(up);

	up *= positionDelta.y * amount;

	rVector3 cameraDelta = right + up;

	m_camera->SetPosition(m_camera->GetPosition() + cameraDelta);
	m_center += cameraDelta;
	m_needsUpdate = true;

	m_lastUpdatePos = position;
	

}

void ModelViewerCamera::Reset(const rVector3 target, float radius, float yaw, float roll) {
	m_center = target;
	m_radius = radius;
	m_distance = radius;
	m_cameraAngle.y = yaw;
	m_cameraAngle.x = roll;

	UpdatePosition();
}

void ModelViewerCamera::UpdatePosition() {
	rQuaternion xform(m_cameraAngle);

	rVector3 cameraVector = rVector3::ForwardVector;
	xform.TransformVector3(cameraVector);

	rVector3 up = rVector3::UpVector;
	xform.TransformVector3(up);

	cameraVector *= m_distance;
	m_camera->SetPosition(m_center + cameraVector);
	m_camera->SetUp(up);

	rVector3 direction = m_center - m_camera->GetPosition();
	direction.Normalize();

	m_camera->SetTarget(m_camera->GetPosition() + direction);

	m_needsUpdate = false;
}

void ModelViewerCamera::SetYaw(float yaw) {
	m_cameraAngle.y = yaw;
	m_needsUpdate = true;
}

float ModelViewerCamera::Yaw() const {
	return m_cameraAngle.y;
}

void ModelViewerCamera::SetRoll(float roll) {
	m_cameraAngle.x = roll;
	m_needsUpdate = true;
}

float ModelViewerCamera::Roll() const {
	return m_cameraAngle.x;
}

float ModelViewerCamera::Radius() const {
	return m_radius;
}

void ModelViewerCamera::SetRadius(float radius) {
	m_radius = radius;
	m_needsUpdate = true;
}

float ModelViewerCamera::Distance() const {
	return m_distance;
}

void ModelViewerCamera::SetDistance(float distance) {
	m_distance = distance;

	float minDistance = m_radius / 10.0f;
	if (m_distance < minDistance)
		m_distance = minDistance;

	m_needsUpdate = true;
}

void ModelViewerCamera::MoveCloserIn() {
	float step = m_radius / 10.0f;
	SetDistance(m_distance - step);
}

void ModelViewerCamera::MoveFartherAway() {
	float step = m_radius / 10.0f;
	SetDistance(m_distance + step);
}

void ModelViewerCamera::SetTarget(const rVector3& target) {
	m_center = target;
	m_needsUpdate = true;
}

rString ModelViewerCamera::ClassName() const {
	return "Temp";
}