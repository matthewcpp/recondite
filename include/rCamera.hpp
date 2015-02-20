#ifndef R_CAMERA_HPP
#define R_CAMERA_HPP

#include "rBuild.hpp"
#include "rActor3.hpp"

#include "interface/riCamera.hpp"
#include "rMathUtil.hpp"

class RECONDITE_API rCamera : public rActor3, public riCamera{
public:
	rCamera(const rString& id , rEngine* engine);

	virtual rVector3 Position() const;
	virtual rVector3 Up() const;

	rVector3 Target() const;
	void SetTarget(const rVector3& target);
	virtual rString ClassName() const;

protected:

	rVector3 m_target;
};

#endif
