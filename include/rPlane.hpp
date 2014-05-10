#ifndef R_PLANE_HPP
#define R_PLANE_HPP

#include "rBuild.hpp"
#include "rVector3.hpp"

struct RECONDITE_API rPlane{
	rPlane(){}
	rPlane(const rVector3& n , float dd): normal(n) , d(dd){}
	rPlane(float nx , float ny , float nz, float dd) : normal(nx,ny,nz), d(dd){}

	void Set(const rVector3& n , float dd);
	void Set(float nx, float ny, float nz, float dd);

	float DistanceToPoint(const rVector3& p) const;
	int Side(const rVector3& p) const;

	rVector3 normal;
	float d;
};

#endif
