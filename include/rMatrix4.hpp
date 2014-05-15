#ifndef R_MATRIX4_T_HPP
#define R_MATRIX4_T_HPP

/*
Matrix4 Layout
[ 0][ 4][ 8][12]
[ 1][ 5][ 9][13]
[ 2][ 6][10][14]
[ 3][ 7][11][15]
*/

#include <cstring>

#include "rBuild.hpp"

#include "rVector3.hpp"
#include "rVector4.hpp"
#include "rMathUtil.hpp"

struct RECONDITE_API rMatrix4{

	rMatrix4();
	rMatrix4(const rMatrix4& matrix);
	rMatrix4(float* data);

	void LoadIdentity();

	void SetUniformScale(float k);
	void SetScale(const rVector3& s);

	rVector3 GetTranslate() const;
	void SetTranslate (float tx, float ty , float tz);
	void SetTranslate (const rVector3& t);

	bool Invert();
	bool GetInvertedMatrix(rMatrix4& m) const;

	rVector3 GetTransformedVector3(const rVector3& v) const;
	void TransformVector3(rVector3& v) const;
	
	rVector4 GetTransformedVector4(const rVector4& v) const;
	void TransformVector4(rVector4& v) const;
	
	void SetRotationX(float deg);
	void SetRotationY(float deg);
	void SetRotationZ(float deg);

	rMatrix4& operator *=(float k);
	rMatrix4 operator *(float k) const;
	
	rMatrix4& operator +=(const rMatrix4& b);
	rMatrix4 operator +(const rMatrix4& b) const;
	rMatrix4& operator -=(const rMatrix4& b);
	rMatrix4 operator -(const rMatrix4& b) const;

	rMatrix4 operator *(const rMatrix4& b) const;
	rMatrix4& operator *=(const rMatrix4& b);

	float m[16];

	operator float*(){return &m[0];}

	static const rMatrix4 IdentityMatrix;
};

#endif
