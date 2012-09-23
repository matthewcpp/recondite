#ifndef R_TRIANGLE2_HPP
#define R_TRIANGLE2_HPP

#include "rVector2.hpp"

struct rTriangle2{
	rTriangle2(){}
	rTriangle2(const rVector2& tp0 , const rVector2& tp1, const rVector2& tp2);

	void Set(const rVector2& tp0 , const rVector2& tp1, const rVector2& tp2);

	bool ContainsPoint(const rVector2& p) const;

	rVector2 p0;
	rVector2 p1;
	rVector2 p2;
};

#endif