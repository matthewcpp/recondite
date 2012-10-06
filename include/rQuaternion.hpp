#ifndef R_QUATERNION_HPP
#define R_QUATERNION_HPP

#include <cmath>

#include "rVector3.hpp"
#include "rMath.hpp"

struct rQuaternion{
	rQuaternion(){};
	rQuaternion(float xx , float yy , float zz , float ww) : x(xx) , y(yy) , z(zz) , w(ww){};
	rQuaternion(const rVector3& eulerAngles);
	rQuaternion(float tx , float ty, float tz);

	void SetFromEulerAngles(const rVector3& angles);
	void SetFromEulerAngles(float tx , float ty, float tz);

	void TransformVector3(rVector3& v) const;
	rVector3 GetTransformedVector3(const rVector3& v) const;

	float Length() const;
	float LengthSquared() const;

	void Normalize();

	static rQuaternion Slerp(const rQuaternion& q1 , const rQuaternion& q2, float t);

	float x , y ,z , w;
};

#endif