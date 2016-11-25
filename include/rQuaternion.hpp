#ifndef R_QUATERNION_HPP
#define R_QUATERNION_HPP

#include <cmath>

#include "rBuild.hpp"
#include "rVector3.hpp"
#include "rMathUtil.hpp"

struct RECONDITE_API rQuaternion{
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

	rQuaternion operator* (const rQuaternion& q);
	

	float Length() const;
	float LengthSquared() const;

	void Normalize();

	static rQuaternion CreateRotationFromVectors(const rVector3& v1, const rVector3& v2);
	static void ToEuler(const rQuaternion& q1, rVector3& v);
	static rQuaternion Slerp(const rQuaternion& q1 , const rQuaternion& q2, float t);

	bool operator==(const rQuaternion& q) const;
	bool operator!=(const rQuaternion& q) const;

	static const rQuaternion Identity;

	float x , y ,z , w;
};

#endif