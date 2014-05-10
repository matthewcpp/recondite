#ifndef R_PLANE_HPP
#define R_PLANE_HPP

#include "rBuild.hpp"
#include "rVector3.hpp"

struct RECONDITE_API rPlane{
	rPlane(){}
	rPlane(const rVector3& n , float dd): normal(n) , d(dd){}
	rPlane(float a , float b , float c, float dd) : normal(a,b,c), d(dd){}

	void Set(const rVector3& n , float dd);

	float DistanceToPoint(const rVector3& p) const;
	int Side(const rVector3& p) const;

	rVector3 normal;
	float d;
};

#endif
