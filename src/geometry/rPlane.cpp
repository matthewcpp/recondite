#include "rPlane.hpp"

float rPlane::DistanceToPoint(const rVector3& p) const{
	rVector3 planePoint = normal * -d;
	return normal.Dot(p - planePoint);
}

int rPlane::Side(const rVector3& p) const{
	float dist = DistanceToPoint(p);

	if (dist < 0.0f)
		return -1;
	else if (dist > 0.0f)
		return 1;
	else
		return 0;
}

void rPlane::Set(const rVector3& n , float dd){
	normal = n;
	d = dd;
}
void rPlane::Set(float nx, float ny, float nz, float dd){
	normal.Set(nx,ny,nz);
	d = dd;
}
