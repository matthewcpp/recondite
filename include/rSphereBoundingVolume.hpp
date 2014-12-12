#ifndef R_SPHEREBOUNDINGVOLUME_HPP
#define R_SPHEREBOUNDINGVOLUME_HPP

#include "rBuild.hpp"

#include "interface/riBoundingVolume.hpp"
#include "rAlignedBox3.hpp"
#include "rIntersection.hpp"
#include "rSphere.hpp"

class RECONDITE_API rSphereBoundingVolume : public riBoundingVolume{
public:
	virtual bool IntersectsRay(const rRay3& ray) const;
	virtual bool IntersectsRay(const rRay3& ray, rVector3* position) const;
	virtual rAlignedBox3 FitBox() const;

	void SetSphere(const rSphere& sphere);

private:
	rSphere m_sphere;
};

#endif