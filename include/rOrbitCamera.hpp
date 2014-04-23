#ifndef R_ORBITCAMERA_HPP
#define R_ORBITCAMERA_HPP

#include "rBuild.hpp"
#include "rCamera.hpp"

class RECONDITE_API rOrbitCamera : public rCamera {
public:
	rOrbitCamera(const rString& name , const rVector3& position);

	virtual int Update(rEngine& engine);

	void SetYaw(float yaw);
	float Yaw() const;

	void SetRoll(float roll);
	float Roll() const;

	float Radius() const;
	void SetRadius(float radius);

	float Distance() const;
	void SetDistance(float distance);

	void MoveCloserIn();
	void MoveFartherAway();

	void Reset(const rVector3 target, float radius, float yaw, float roll);

	virtual void SetTarget(const rVector3& target);
	virtual rVector3 Target() const;

	void UpdatePosition();

private:

	float m_radius;
	float m_distance;

	bool m_needsUpdate;
};

#endif