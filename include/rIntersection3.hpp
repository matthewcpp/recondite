#ifndef R_COLLISIONS3_HPP
#define R_COLLISIONS3_HPP

#include "rAlignedBox3.hpp"
#include "rSphere3.hpp"
#include "rLine3.hpp"
#include "rPlane3.hpp"
#include "rCone3.hpp"

#include "rMathUtil.hpp"

namespace rIntersection3{

	bool AlignedBoxIntersectsSphere(const rAlignedBox3& box , const rSphere3& sphere);
	bool SphereContainsAlignedBox(const rSphere3& sphere, const rAlignedBox3& box);

	bool AlignedBoxContainsSphere(const rAlignedBox3& box , const rSphere3& sphere);

	bool RayIntersectsAlignedBox(const rRay3& ray,const rAlignedBox3& box );
	bool RayIntersectsPlane(const rRay3& ray , const rPlane3& plane, rVector3* point = 0);
	bool RayIntersectsSphere(const rRay3& ray , const rSphere3& sphere);

	int RayIntersectsCone(const rRay3& ray , const rCone3& cone);
}

#endif