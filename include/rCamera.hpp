#ifndef R_CAMERA_HPP
#define R_CAMERA_HPP

#include "rBuild.hpp"
#include "rActor3.hpp"

#include "interface/riCamera.hpp"
#include "rMathUtil.hpp"

class RECONDITE_API rCamera : public rActor3, public riCamera{
public:
	rCamera(const rString& name , const rVector3& position);

	virtual int Update(rEngine& engine);
	virtual rVector3 Position() const;
	virtual rVector3 Up() const;

protected:

	rVector3 m_target;
};

class RECONDITE_API rViewCamera : public rCamera{
public:
	rViewCamera(const rString& name , const rVector3& position);
	virtual rString ClassName() const;


	virtual rVector3 Target() const;
};

class RECONDITE_API rTargetCamera : public rCamera{
public: 
	rTargetCamera(const rString& name , const rVector3& position);
	
	virtual rVector3 Target() const;
	virtual void SetTarget(const rVector3& target);
	virtual rString ClassName() const;
};

#endif
