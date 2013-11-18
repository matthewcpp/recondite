#ifndef R_MATH_UTILS_HPP
#define R_MATH_UTILS_HPP

#include <algorithm>

#include "rTypes.hpp"
#include "rRectangle2.hpp"
#include "rCircle2.hpp"
#include "rMatrix3.hpp"
#include "rLine2.hpp"

#include "rVector3.hpp"

#ifndef M_PI
	#define M_PI 3.141592653589793238462643f
#endif

#define rMATH_ZERO_TOLERANCE 1e-06f

namespace rMath{
	float DegreeToRad(float deg);
	float RadToDeg(float rad);

	float ConvertRange(float value, float inMin, float inMax, float outMin, float outMax);

	float Max3(float n1 , float n2, float n3);

	template <typename T>
	T Clamp(const T& val, const T& min, const T& max);

	bool PointInBoundedXYPlane(const rVector3& corner1 , const rVector3& corner2 , const rVector3& point);
	bool PointInBoundedXZPlane(const rVector3& corner1 , const rVector3& corner2 , const rVector3& point);
	bool PointInBoundedYZPlane(const rVector3& corner1 , const rVector3& corner2 , const rVector3& point);
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
