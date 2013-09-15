#include "rCamera.hpp"


rCamera::rCamera(const rString& name , const rVector3& position)
	:rActor3(name , position)
{}

rViewCamera::rViewCamera(const rString& name , const rVector3& position)
	:rCamera(name , position)
{

}

rVector3 rViewCamera::Target() const{
	rVector3 forward = Forward();
	forward *= 10.0f;
	return m_position + forward;
}

int rViewCamera::Update(const rTime& gameTime){
	return 0;
}


rTargetCamera::rTargetCamera(const rString& name , const rVector3& position)
	:rCamera(name , position)
{

}

int rTargetCamera::Update(const rTime& gameTime){
	return 0;
}
	
rVector3 rTargetCamera::Target() const{
	return m_target;
}

void rTargetCamera::SetTarget(const rVector3& target){
	m_target = target;
}