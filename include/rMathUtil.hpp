#ifndef R_MATH_UTILS_HPP
#define R_MATH_UTILS_HPP

#include <algorithm>

#include "rBuild.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

#define rMATH_ZERO_TOLERANCE 1e-06f

namespace rMath{
	 float RECONDITE_API DegreeToRad(float deg);
	float RECONDITE_API RadToDeg(float rad);

	float RECONDITE_API ConvertRange(float value, float inMin, float inMax, float outMin, float outMax);

	float RECONDITE_API Max3(float n1 , float n2, float n3);

	template <typename T>
	T Clamp(const T& val, const T& min, const T& max);

	template <typename T>
	int RoundToInt(T r);
};

template <typename T>
int rMath::RoundToInt(T r) {
  int tmp = static_cast<int> (r);
  tmp += (r - tmp >= 0.5) - (r - tmp <= -0.5);
  return tmp;
}

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
