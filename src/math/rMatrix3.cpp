#include "rMatrix3.hpp"

const rMatrix3 rMatrix3::IdentityMatrix = rMatrix3();

rMatrix3::rMatrix3(){
	LoadIdentity();
}


void rMatrix3::SetTranslate(float tx , float ty){
	rVector2 t(tx , ty);
	SetTranslate(t);
}


void rMatrix3::SetTranslate(const rVector2& t){
	m[6] = t.x;
	m[7] = t.y;
}


void rMatrix3::SetUniformScale(float s){
	m[0] = s;
	m[4] = s;
	m[8] = s;
}


void rMatrix3::LoadIdentity(){
	memset(this , 0 , sizeof(rMatrix3) );
	SetUniformScale(1.0);
}


void rMatrix3::TransformVector2(rVector2& v) const{
	rVector2 r;

	r.x = m[0] * v.x + m[3] * v.y + m[6];
	r.y = m[1] * v.x + m[4] * v.y + m[7];

	v = r;
}


rVector2 rMatrix3::GetTransformedVector2(const rVector2& v) const{
	rVector2 tv = v;
	TransformVector2(tv);
	return tv;
}


float rMatrix3:: Determinant() const{
	return	  m[0] * (m[8] * m[4] - m[5] * m[7]) 
			- m[1] * (m[8] * m[3] - m[5] * m[6]) 
			+ m[2] * (m[7] * m[3] - m[4] * m[6]);
}


void rMatrix3::Invert(){
	float det = Determinant();

	if (det == 0.0)
		return;

	rMatrix3 result;

	result.m[0] = m[4] * m[8] - m[7] * m[5];
	result.m[1] = m[7] * m[2] - m[1] * m[8];
	result.m[2] = m[1] * m[5] - m[4] * m[2];

	result.m[3] = m[6] * m[5] - m[3] * m[8];
	result.m[4] = m[0] * m[8] - m[6] * m[2];
	result.m[5] = m[3] * m[2] - m[0] * m[5];

	result.m[6] = m[3] * m[7] - m[6] * m[4];
	result.m[7] = m[6] * m[1] - m[0] * m[7];
	result.m[8] = m[0] * m[4] - m[3] * m[1];

	result *= det;

	*this = result;
}


rMatrix3 rMatrix3::GetInvertedMatrix() const{
	rMatrix3 result = *this;
	result.Invert();
	return result;
}


rMatrix3& rMatrix3::operator *=(float k){
	m[0] *= k;	m[3] *= k;	m[6] *= k;
	m[1] *= k;	m[4] *= k;	m[7] *= k;
	m[2] *= k;	m[5] *= k;	m[8] *= k;

	return *this;
}
