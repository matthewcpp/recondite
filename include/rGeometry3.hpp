#ifndef R_GEOMETRY3_HPP
#define R_GEOMETRY3_HPP

#include "rAlignedBox3.hpp"
#include "rSphere3.hpp"
#include "rCone3.hpp"

namespace rGeometry3{
	void FitAlignedBoxToSphere(rAlignedBox3& box , const rSphere3& sphere);
	void FitSphereToAlignedBox(rSphere3& sphere , const rAlignedBox3& box);
	void FitAlignedBoxToCone(rAlignedBox3& box, const rCone3& cone);
};

#endif
