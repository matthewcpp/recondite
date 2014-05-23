#ifndef R_SPHERE3_HPP
#define R_SPHERE3_HPP

#include "rBuild.hpp"

#include "rVector3.hpp"

struct RECONDITE_API rSphere{

	rSphere(){}
	rSphere(const rVector3& ccenter , float rradius) : center(ccenter) , radius(rradius){}
	rSphere(float centerX , float centerY , float centerZ , float r) : center (centerX, centerY, centerZ), radius(r){}

	bool ContainsPoint(const rVector3& p) const;
	void Set(float cx, float cy, float cz, float r);

	rVector3 center;
	float radius;
};

#endif