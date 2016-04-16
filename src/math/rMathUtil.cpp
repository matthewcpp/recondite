#include "rMathUtil.hpp"

float rMath::DegreeToRad(float deg){
	return deg * (M_PI / 180.0f);
}

float rMath::RadToDeg(float rad){
	return rad * (180.0f / M_PI);
}

float rMath::ConvertRange(float value, float inMin, float inMax, float outMin, float outMax){
    return outMin + ((value - inMin) / (inMax - inMin)) * (outMax - outMin);
}

float rMath::Max3(float n1 , float n2, float n3){
	if (n1 > n2){
		if (n1 > n3)
			return n1;
		else
			return n3;
	}
	else{
		if (n2 > n3)
			return n2;
	}
	
	return n3;
}

uint32_t rMath::NextHighestPowerOf2(uint32_t v){
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	v += (v == 0);

	return v;
}