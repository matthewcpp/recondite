#ifndef R_VECTOR4_HPP
#define R_VECTOR4_HPP

#include "rBuild.hpp"

struct RECONDITE_API rVector4{
	rVector4() {}
	rVector4(float xx, float yy, float zz, float ww) : x(xx), y(yy), z(zz), w(ww) {}
	
	rVector4& operator /= (float k);
	rVector4 operator / (float k);
	
	float x, y , z, w;
};

#endif
