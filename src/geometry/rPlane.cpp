#include "rPlane.hpp"

rPlane::rPlane(const rVector3& pt, const rVector3& n){
	SetFromPointAndNormal(pt,n);
}

float rPlane::DistanceToPoint(const rVector3& p) const{
	return normal.Dot(p) + d;
}

void rPlane::Normalize(){
	float len = normal.Length();

	if (len != 0.0f){
		float invLen = 1.0f / len;
		normal *= invLen;
		d *= invLen;
	}
}

int rPlane::Side(const rVector3& p) const{
	float distance = DistanceToPoint(p);

	if (distance > 0.0f)
		return 1;
	else if (distance < 0.0f)
		return -1;
	else
		return 0;
}

void rPlane::SetFromPointAndNormal(const rVector3& pt, const rVector3 n){
	normal = n;
    d = -n.Dot(pt);
}

void rPlane::Set(float nx , float ny , float nz, float dd){
	normal.Set(nx, ny, nz);
	d = dd;
}
