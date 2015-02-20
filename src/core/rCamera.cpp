#include "rCamera.hpp"


rCamera::rCamera(const rString& id , rEngine* engine)
	:rActor3(id , engine)
{
	m_target = rVector3::ZeroVector;
}

rVector3 rCamera::Position() const{
	return rActor3::Position();
}

rVector3 rCamera::Up() const{
	return rActor3::Up();
}

rVector3 rCamera::Target() const{
	return m_target;
}

void rCamera::SetTarget(const rVector3& target){
	m_target = target;
}

rString rCamera::ClassName() const{
	return "Camera";
}
