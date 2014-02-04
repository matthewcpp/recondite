#ifndef R_CAMERA_HPP
#define R_CAMERA_HPP

#include "rTypes.hpp"
#include "rActor3.hpp"

#include "interface/riCamera.hpp"
#include "rMathUtil.hpp"

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

class rOrbitCamera : public rCamera {
public:
	rOrbitCamera(const rString& name , const rVector3& position);

	void SetYaw(float yaw);
	float Yaw() const;

	void SetRoll(float roll);
	float Roll() const;

	void Orbit(float yaw, float roll, float zoom);

	float Radius() const;
	void SetRadius(float radius);

	void Reset(const rVector3 target, float radius, float yaw, float roll);

	virtual void SetTarget(const rVector3& target);
	virtual rVector3 Target() const;

private:
	void UpdatePosition();

private:

	float m_yaw;
	float m_roll;
	float m_radius;
};

#endif
