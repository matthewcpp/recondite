#ifndef R_QUATERNION_HPP
#define R_QUATERNION_HPP

#include <cmath>

#include "rVector3.hpp"
#include "rMathUtil.hpp"

struct rQuaternion{
	rQuaternion(){};
	rQuaternion(float xx , float yy , float zz , float ww) : x(xx) , y(yy) , z(zz) , w(ww){};
	rQuaternion(const rVector3& eulerAngles);
	rQuaternion(float tx , float ty, float tz);
	rQuaternion(const rVector3& axis, float degrees);

	void SetFromEulerAngles(const rVector3& angles);
	void SetFromEulerAngles(float tx , float ty, float tz);

	void SetFromAxisAngle(float axisx, float axisy, float axisz, float degrees);
	void SetFromAxisAngle(const rVector3& axis, float degrees);

	void TransformVector3(rVector3& v) const;
	rVector3 GetTransformedVector3(const rVector3& v) const;

	float Length() const;
	float LengthSquared() const;

	void Normalize();

	static rQuaternion Slerp(const rQuaternion& q1 , const rQuaternion& q2, float t);

	static const rQuaternion Identity;

	float x , y ,z , w;
};

#endif