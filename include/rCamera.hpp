#ifndef R_CAMERA_HPP
#define R_CAMERA_HPP

#include "rTypes.hpp"
#include "rActor3.hpp"

#include "interface/riCamera.hpp"

class rCamera : public rActor3, public riCamera{
public:
	rCamera(const rString& name , const rVector3& position);

	virtual int Update(rEngine& engine);
	virtual rVector3 Position() const;
	virtual rVector3 Up() const;

protected:

	rVector3 m_target;
};

class rViewCamera : public rCamera{
public:
	rViewCamera(const rString& name , const rVector3& position);


	virtual rVector3 Target() const;
};

class rTargetCamera : public rCamera{
public: 
	rTargetCamera(const rString& name , const rVector3& position);
	
	virtual rVector3 Target() const;
	virtual void SetTarget(const rVector3& target);
};

#endif
