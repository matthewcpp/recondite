#ifndef R_SPHERE3_HPP
#define R_SPHERE3_HPP

#include "rVector3.hpp"

struct rSphere3{

	rSphere3(){}
	rSphere3(const rVector3& ccenter , float rradius) : center(ccenter) , radius(rradius){}
	rSphere3(float centerX , float centerY , float centerZ , float r);

	bool ContainsPoint(const rVector3& p) const;

	rVector3 center;
	float radius;
};

#endif