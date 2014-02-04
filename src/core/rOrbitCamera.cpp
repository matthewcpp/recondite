#include "rOrbitCamera.hpp"

rOrbitCamera::rOrbitCamera(const rString& name , const rVector3& position)
	:rCamera(name, position)
{
	Reset(rVector3::ZeroVector, 1.0f, 0.0f, 0.0f);
}

void rOrbitCamera::UpdatePosition(){
	rQuaternion xform(m_rotation);
	rVector3 cameraVector = rVector3::ForwardVector;
	xform.TransformVector3(cameraVector);
	cameraVector *= m_distance;
	m_position = m_target + cameraVector;

	m_needsUpdate = false;
}

void rOrbitCamera::SetYaw(float yaw){
	m_rotation.y = yaw;
	m_needsUpdate = true;
}

float rOrbitCamera::Yaw() const{
	return m_rotation.y;
}

void rOrbitCamera::SetRoll(float roll){
	m_rotation.x = roll;
	m_needsUpdate = true;
}

float rOrbitCamera::Roll() const{
	return m_rotation.x;
}

float rOrbitCamera::Radius() const{
	return m_radius;
}

void rOrbitCamera::SetRadius(float radius){
	m_radius = radius;
	m_needsUpdate = true;
}

void rOrbitCamera::SetTarget(const rVector3& target){
	m_target = target;
	m_needsUpdate = true;
}

void rOrbitCamera::Reset(const rVector3 target, float radius, float yaw, float roll){
	m_target = target;
	m_radius = radius;
	m_distance = radius;
	m_rotation.y = yaw;
	m_rotation.x = roll;

	UpdatePosition();
}

rVector3 rOrbitCamera::Target() const{
	return m_target;
}

int rOrbitCamera::Update(rEngine& engine){
	if (m_needsUpdate)
		UpdatePosition();

	return 0;
}

float rOrbitCamera::Distance() const{
	return m_distance;
}

void rOrbitCamera::SetDistance(float distance){
	m_distance = distance;

	float minDistance = m_radius / 10.0f;
	if (m_distance < minDistance)
		m_distance = minDistance;

	m_needsUpdate = true;
}

void rOrbitCamera::MoveCloserIn(){
	float step = m_radius / 10.0f;
	SetDistance(m_distance - step);
}

void rOrbitCamera::MoveFartherAway(){
	float step = m_radius / 10.0f;
	SetDistance(m_distance + step);
}