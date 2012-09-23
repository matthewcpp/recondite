#ifndef R_PLANE3_HPP
#define R_PLANE3_HPP

#include "rVector3.hpp"

struct rPlane3{
	rPlane3(){}
	rPlane3(const rVector3& n , float dd): normal(n) , d(dd){}
	rPlane3(float a , float b , float c, float dd) : normal(a,b,c), d(dd){}

	void Set(const rVector3& n , float dd);

	float DistanceToPoint(const rVector3& p) const;
	int Side(const rVector3& p) const;

	rVector3 normal;
	float d;
};

#endif
