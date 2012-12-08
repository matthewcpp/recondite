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
