#include "rSphere.hpp"

bool rSphere::ContainsPoint(const rVector3& p) const{
	return center.Distance(p) <= radius;
}

void rSphere::Set(float cx, float cy, float cz, float r){
	center.x = cx;
	center.y = cy;
	center.z = cz;
	radius = r;
}