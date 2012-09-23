#include "rTriangle2.hpp"

rTriangle2::rTriangle2(const rVector2& tp0 , const rVector2& tp1, const rVector2& tp2){
	Set(tp0 , tp1 , tp2);
}

void rTriangle2::Set(const rVector2& tp0 , const rVector2& tp1, const rVector2& tp2){
	p0 = tp0;
	p1 = tp1;
	p2 = tp2;
}

bool rTriangle2::ContainsPoint(const rVector2& p) const{

	rVector2 AB = p1 - p0;
	rVector2 BC = p2 - p1;
	rVector2 CA = p0 - p2;

	rVector2 AP = p - p0;
	rVector2 BP = p - p1;
	rVector2 CP = p - p2;

	if ( AP.Cross(AB) >= 0.0f)
		return (BP.Cross(BC) >= 0.0f) && (CP.Cross(CA) >= 0.0f );
	else 
		return (BP.Cross(BC) <= 0.0f) && (CP.Cross(CA) <= 0.0f );
}