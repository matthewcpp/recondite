#include "rCamera.hpp"


rCamera::rCamera(const rString& name , const rVector3& position)
	:rActor3(name , position)
{}

rVector3 rCamera::Position() const{
	return rActor3::Position();
}

rVector3 rCamera::Up() const{
	return rActor3::Up();
}

int rCamera::Update(rEngine& engine){
	return 0;
}

rViewCamera::rViewCamera(const rString& name , const rVector3& position)
	:rCamera(name , position)
{

}

rVector3 rViewCamera::Target() const{
	rVector3 forward = Forward();
	forward *= 10.0f;
	return m_position + forward;
}


//------------------------------------------

rTargetCamera::rTargetCamera(const rString& name , const rVector3& position)
	:rCamera(name , position)
{

}

rVector3 rTargetCamera::Target() const{
	return m_target;
}

void rTargetCamera::SetTarget(const rVector3& target){
	m_target = target;
}


//------------------------------------------

rOrbitCamera::rOrbitCamera(const rString& name , const rVector3& position)
	:rCamera(name, position)
{
	Reset(rVector3::ZeroVector, 1.0f, 0.0f, 0.0f);
}

void rOrbitCamera::UpdatePosition(){
	rQuaternion xform(m_rotation);
	rVector3 cameraVector = rVector3::ForwardVector;
	xform.TransformVector3(cameraVector);
	cameraVector *= m_radius;
	m_position = m_target + cameraVector;
}

void rOrbitCamera::SetYaw(float yaw){
	m_rotation.y = yaw;

	UpdatePosition();
}

float rOrbitCamera::Yaw() const{
	return m_rotation.y;
}

void rOrbitCamera::Orbit(float yaw, float roll, float zoom){
	m_rotation.y += yaw;
	m_rotation.x += roll;
	m_radius += zoom;

	UpdatePosition();
}

void rOrbitCamera::SetRoll(float roll){
	m_rotation.x = roll;

	UpdatePosition();

}

float rOrbitCamera::Roll() const{
	return m_rotation.x;
}

float rOrbitCamera::Radius() const{
	return m_radius;
}

void rOrbitCamera::SetRadius(float radius){
	m_radius = radius;
	UpdatePosition();
}

void rOrbitCamera::SetTarget(const rVector3& target){
	m_target = target;

	UpdatePosition();
}

void rOrbitCamera::Reset(const rVector3 target, float radius, float yaw, float roll){
	m_target = target;
	m_radius = radius;
	m_rotation.y = yaw;
	m_rotation.x = roll;

	UpdatePosition();
}

rVector3 rOrbitCamera::Target() const{
	return m_target;
}