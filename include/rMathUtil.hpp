#ifndef R_MATH_UTILS_HPP
#define R_MATH_UTILS_HPP

#include <algorithm>
#include <cstdint>

#include "rBuild.hpp"

#define rMATH_ZERO_TOLERANCE 1e-06f
#define rPI       3.14159265358979323846
#define rPI_2     1.57079632679489661923f

namespace rMath{
	float RECONDITE_API DegreeToRad(float deg);
	float RECONDITE_API RadToDeg(float rad);

	float RECONDITE_API ConvertRange(float value, float inMin, float inMax, float outMin, float outMax);

	float RECONDITE_API Max3(float n1 , float n2, float n3);
	uint32_t RECONDITE_API NextHighestPowerOf2(uint32_t v);

	template <typename T>
	T Clamp(const T& val, const T& min, const T& max);
};



template <typename T>
T rMath::Clamp(const T& val, const T& min, const T& max){
	if (val > max)
		return max;
	else if (val < min)
		return min;
	else
		return val;
}

#endif
