#include "rPlane3.hpp"

float rPlane3::DistanceToPoint(const rVector3& p) const{
	rVector3 planePoint = normal * -d;
	return normal.Dot(p - planePoint);
	//return normal.Dot(p) - d;
	//return normal.Dot(p) + d; // d is stored as negative value
}

int rPlane3::Side(const rVector3& p) const{
	float dist = DistanceToPoint(p);

	if (dist < 0.0f)
		return -1;
	else if (dist > 0.0f)
		return 1;
	else
		return 0;
}

void rPlane3::Set(const rVector3& n , float dd){
	normal = n;
	d = dd;
}