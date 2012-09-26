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

#include "rVector3.hpp"
#include "rMathUtil.hpp"

struct rMatrix4{

	rMatrix4();

	void LoadIdentity();

	void SetUniformScale(float k);
	float Determinant() const;

	rVector3 GetTranslate() const;
	void SetTranslate (float tx, float ty , float tz);
	void SetTranslate (const rVector3& t);

	void Invert();
	rMatrix4 GetInvertedMatrix() const;

	rVector3 GetTransformedVector3(const rVector3& v) const;
	void TransformVector3(rVector3& v) const;

	rMatrix4& operator *=(float k);
	rMatrix4 operator *(float k);
	
	rMatrix4& operator +=(const rMatrix4& other);
	rMatrix4& operator -=(const rMatrix4& other);

	float m[16];

	operator float*(){return &m[0];}

	static const rMatrix4 IdentityMatrix;
};

#endif