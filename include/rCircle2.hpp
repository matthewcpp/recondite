#ifndef R_CIRCLE2_T_HPP
#define R_CIRCLE2_T_HPP

#include <algorithm> 

#include "rVector2.hpp"

struct rCircle2{

	rCircle2(){}
	rCircle2(float xx , float yy , float rr) : center(xx,yy) , radius(rr){}
	rCircle2(const rVector2& c , float r) : center(c) , radius(r){}

	void Set(float xx , float yy , float rr);

	bool ContainsPoint(const rVector2& p) const;

	rVector2 center;
	float radius;
};

#endif