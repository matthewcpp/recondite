#include "rSphere.hpp"

rSphere::rSphere(float centerX , float centerY , float centerZ , float r){
	center.Set(centerX , centerY , centerZ);
	radius = r;
}

bool rSphere::ContainsPoint(const rVector3& p) const{
	return center.Distance(p) <= radius;
}