#ifndef R_CONE3_HPP
#define R_CONE3_HPP

#include <cmath>

#include "rVector3.hpp"

struct rCone3{
	rCone3(){}
	rCone3(const rVector3& p , const rVector3& d , float h , float a);

	void Set(const rVector3& p , const rVector3& d , float h , float a);


	float CapRadius() const;

	rVector3 Base() const;

	rVector3 point;
	rVector3 direction;

	float height;
	float angle;
};

#endif