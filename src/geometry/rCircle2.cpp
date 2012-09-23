#include "rCircle2.hpp"

void rCircle2::Set(float xx , float yy , float rr){
	center.x = xx;
	center.y = yy;
	radius = rr;
}

bool rCircle2::ContainsPoint(const rVector2& p) const{
	return center.Distance(p) <= radius;
}