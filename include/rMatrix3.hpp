#ifndef R_MATRIX3_HPP
#define R_MATRIX3_HPP

#include <cstring>

/*
Matrix3 Layout
[ 0][ 3][ 6]	
[ 1][ 4][ 7]	
[ 2][ 5][ 8]	

*/

#include <cmath>

#include "rVector2.hpp"


struct rMatrix3{

	rMatrix3();

	void SetTranslate(float tx , float ty);
	void SetTranslate(const rVector2& t);

	void SetUniformScale(float s);

	void TransformVector2(rVector2& v) const;
	rVector2 GetTransformedVector2(const rVector2& v) const;

	float Determinant() const;
	void Invert();
	rMatrix3 GetInvertedMatrix() const;

	rMatrix3& operator *=(float k);

	void LoadIdentity();

	float m[9];

	static const rMatrix3 IdentityMatrix;
};



#endif