#ifndef R_COLLISIONS3_HPP
#define R_COLLISIONS3_HPP

#include "rBuild.hpp"

#include "rAlignedBox3.hpp"
#include "rSphere.hpp"
#include "rLine3.hpp"
#include "rPlane.hpp"
#include "rFrustrum.hpp"

#include "rMathUtil.hpp"

namespace rIntersection{
	bool RECONDITE_API SphereContainsAlignedBox(const rSphere& sphere, const rAlignedBox3& box);

	bool RECONDITE_API AlignedBoxContainsSphere(const rAlignedBox3& box , const rSphere& sphere);
	bool RECONDITE_API AlignedBoxIntersectsSphere(const rAlignedBox3& box , const rSphere& sphere);

	bool RECONDITE_API RayIntersectsAlignedBox(const rRay3& ray,const rAlignedBox3& box, rVector3* intersectionPoint = NULL );
	bool RECONDITE_API RayIntersectsPlane(const rRay3& ray , const rPlane& plane, rVector3* point = 0);
	bool RECONDITE_API RayIntersectsSphere(const rRay3& ray , const rSphere& sphere);

	bool RECONDITE_API FrustrumContainsSphere(const rFrustrum& frustrum, const rSphere& sphere);
	bool RECONDITE_API FrustrumIntersectsSphere(const rFrustrum& frustrum, const rSphere& sphere);
}

#endif