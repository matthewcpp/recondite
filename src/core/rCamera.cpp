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

rString rViewCamera::ClassName() const{
	return "ViewCamera";
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

rString rTargetCamera::ClassName() const{
	return "TargetCamera";
}