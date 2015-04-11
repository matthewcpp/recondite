#include "rVector4.hpp"

rVector4& rVector4::operator /= (float k){
	x /= k;
	y /= k;
	z /= k;
	w /= k;
	
	return *this;
}

rVector4 rVector4::operator / (float k){
	return rVector4(x / k, y / k, z / k, w / k);
}

rVector4& rVector4::Set(float xx, float yy, float zz, float ww){
	x = xx;
	y = yy;
	z = zz;
	w = ww;

	return *this;
}