#include "rCamera.hpp"


rCamera::rCamera(const rString& id , rEngine* engine)
	:rActor3(id , engine)
{}

rVector3 rCamera::Position() const{
	return rActor3::Position();
}

rVector3 rCamera::Up() const{
	return rActor3::Up();
}

//------------------------------------------

rViewCamera::rViewCamera(const rString& id , rEngine* engine)
	:rCamera(id , engine)
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

rTargetCamera::rTargetCamera(const rString& id , rEngine* engine)
	:rCamera(id , engine)
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