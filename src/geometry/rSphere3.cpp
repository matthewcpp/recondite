#include "rSphere3.hpp"

rSphere3::rSphere3(float centerX , float centerY , float centerZ , float r){
	center.Set(centerX , centerY , centerZ);
	radius = r;
}

bool rSphere3::ContainsPoint(const rVector3& p) const{
	return center.Distance(p) <= radius;
}