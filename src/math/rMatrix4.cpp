#include "rMatrix4.hpp"

const rMatrix4 rMatrix4::IdentityMatrix = rMatrix4();

rMatrix4::rMatrix4(){
	LoadIdentity();
}


void rMatrix4::LoadIdentity(){
	memset(this , 0 , sizeof(rMatrix4) );
	SetUniformScale(1);
}


void rMatrix4::SetUniformScale(float k){
	m[0] = k;
	m[5] = k;
	m[10] = k;
	m[15] = k;
}


rVector3 rMatrix4::GetTranslate() const{
	return rVector3(m[12] , m[13] , m[14]);
}


void rMatrix4::SetTranslate (float tx, float ty , float tz){
	m[12] = tx;
	m[13] = ty;
	m[14] = tz;
}


void rMatrix4::SetTranslate (const rVector3& t){
	m[12] = t.x;
	m[13] = t.y;
	m[14] = t.z;
}


rVector3 rMatrix4::GetTransformedVector3(const rVector3& v) const{
	rVector3 r = v;
	TransformVector3(r);
	return r;
}


void rMatrix4::TransformVector3(rVector3& v)const{
	rVector3 r;
	r.x = m[0] * v.x + m[4] * v.y + m[8] * v.z + m[12];
	r.y = m[1] * v.x + m[5] * v.y + m[9] * v.z + m[13];
	r.z = m[2] * v.x + m[6] * v.y + m[10] * v.z + m[14];
	v = r;
}


float rMatrix4::Determinant() const{
return      m[12] * m[9] * m[6] * m[3]-m[8] * m[13] * m[6] * m[3]-m[12] * m[5] * m[10] * m[3]+m[4] * m[13] * m[10] * m[3]+
      m[8] * m[5] * m[14] * m[3]-m[4] * m[9] * m[14] * m[3]-m[12] * m[9] * m[2] * m[7]+m[8] * m[13] * m[2] * m[7]+
      m[12] * m[1] * m[10] * m[7]-m[0] * m[13] * m[10] * m[7]-m[8] * m[1] * m[14] * m[7]+m[0] * m[9] * m[14] * m[7]+
      m[12] * m[5] * m[2] * m[11]-m[4] * m[13] * m[2] * m[11]-m[12] * m[1] * m[6] * m[11]+m[0] * m[13] * m[6] * m[11]+
      m[4] * m[1] * m[14] * m[11]-m[0] * m[5] * m[14] * m[11]-m[8] * m[5] * m[2] * m[15]+m[4] * m[9] * m[2] * m[15]+
      m[8] * m[1] * m[6] * m[15]-m[0] * m[9] * m[6] * m[15]-m[4] * m[1] * m[10] * m[15]+m[0] * m[5] * m[10] * m[15];
}


void rMatrix4::Invert(){
	float det = Determinant();
	if (det == 0.0)
		return;

	rMatrix4 result;

	result.m[0] = m[9]*m[14]*m[7] - m[13]*m[10]*m[7] + m[13]*m[6]*m[11] - m[5]*m[14]*m[11] - m[9]*m[6]*m[15] + m[5]*m[10]*m[15];
	result.m[1] = m[13]*m[10]*m[3] - m[9]*m[14]*m[3] - m[13]*m[2]*m[11] + m[1]*m[14]*m[11] + m[9]*m[2]*m[15] - m[1]*m[10]*m[15];
	result.m[2] = m[5]*m[14]*m[3] - m[13]*m[6]*m[3] + m[13]*m[2]*m[7] - m[1]*m[14]*m[7] - m[5]*m[2]*m[15] + m[1]*m[6]*m[15];
	result.m[3] = m[9]*m[6]*m[3] - m[5]*m[10]*m[3] - m[9]*m[2]*m[7] + m[1]*m[10]*m[7] + m[5]*m[2]*m[11] - m[1]*m[6]*m[11];
	   
	   
	result.m[4] = m[12]*m[10]*m[7] - m[8]*m[14]*m[7] - m[12]*m[6]*m[11] + m[4]*m[14]*m[11] + m[8]*m[6]*m[15] - m[4]*m[10]*m[15];
	result.m[5] = m[8]*m[14]*m[3] - m[12]*m[10]*m[3] + m[12]*m[2]*m[11] - m[0]*m[14]*m[11] - m[8]*m[2]*m[15] + m[0]*m[10]*m[15];
	result.m[6] = m[12]*m[6]*m[3] - m[4]*m[14]*m[3] - m[12]*m[2]*m[7] + m[0]*m[14]*m[7] + m[4]*m[2]*m[15] - m[0]*m[6]*m[15];
	result.m[7] = m[4]*m[10]*m[3] - m[8]*m[6]*m[3] + m[8]*m[2]*m[7] - m[0]*m[10]*m[7] - m[4]*m[2]*m[11] + m[0]*m[6]*m[11];
			 
	result.m[8] = m[8]*m[13]*m[7] - m[12]*m[9]*m[7] + m[12]*m[5]*m[11] - m[4]*m[13]*m[11] - m[8]*m[5]*m[15] + m[4]*m[9]*m[15];
	result.m[9] = m[12]*m[9]*m[3] - m[8]*m[13]*m[3] - m[12]*m[1]*m[11] + m[0]*m[13]*m[11] + m[8]*m[1]*m[15] - m[0]*m[9]*m[15];
	result.m[10] = m[4]*m[13]*m[3] - m[12]*m[5]*m[3] + m[12]*m[1]*m[7] - m[0]*m[13]*m[7] - m[4]*m[1]*m[15] + m[0]*m[5]*m[15];
	result.m[11] = m[8]*m[5]*m[3] - m[4]*m[9]*m[3] - m[8]*m[1]*m[7] + m[0]*m[9]*m[7] + m[4]*m[1]*m[11] - m[0]*m[5]*m[11];
	   
	result.m[12] = m[12]*m[9]*m[6] - m[8]*m[13]*m[6] - m[12]*m[5]*m[10] + m[4]*m[13]*m[10] + m[8]*m[5]*m[14] - m[4]*m[9]*m[14];
	result.m[13] = m[8]*m[13]*m[2] - m[12]*m[9]*m[2] + m[12]*m[1]*m[10] - m[0]*m[13]*m[10] - m[8]*m[1]*m[14] + m[0]*m[9]*m[14];
	result.m[14] = m[12]*m[5]*m[2] - m[4]*m[13]*m[2] - m[12]*m[1]*m[6] + m[0]*m[13]*m[6] + m[4]*m[1]*m[14] - m[0]*m[5]*m[14];
	result.m[15] = m[4]*m[9]*m[2] - m[8]*m[5]*m[2] + m[8]*m[1]*m[6] - m[0]*m[9]*m[6] - m[4]*m[1]*m[10] + m[0]*m[5]*m[10];

	result *= (1.0f / det);

	*this = result;
}


rMatrix4 rMatrix4::GetInvertedMatrix()const{
	rMatrix4 r = *this;
	r.Invert();
	return r;
}


rMatrix4& rMatrix4::operator *=(float k){
	m[0] *= k;	m[4] *= k;	m[8] *= k;	m[12] *= k;
	m[1] *= k;	m[5] *= k;	m[9] *= k;	m[13] *= k;
	m[2] *= k;	m[6] *= k;	m[10] *= k;	m[14] *= k;  
	m[3] *= k;	m[7] *= k;	m[11] *= k;	m[15] *= k;        

	return *this;                                          
}     

rMatrix4 rMatrix4::operator *(float k){
	rMatrix4 r;
	
	r.m[0] = m[0] * k;	r.m[4] = m[4] * k;	r.m[8]  = m[8]  * k;	r.m[12] = m[12] * k;
	r.m[1] = m[1] * k;	r.m[5] = m[5] * k;	r.m[9]  = m[9]  * k;	r.m[13] = m[13] * k;
	r.m[2] = m[2] * k;	r.m[6] = m[6] * k;	r.m[10] = m[10] * k;	r.m[14] = m[14] * k;  
	r.m[3] = m[3] * k;	r.m[7] = m[7] * k;	r.m[11] = m[11] * k;	r.m[15] = m[15] * k;  
	
	return r;
}
                  
rMatrix4& rMatrix4::operator +=(const rMatrix4& b){
	m[0] += b.m[0];	m[4] += b.m[4];	m[8]  += b.m[8] ;	m[12] += b.m[12];
	m[1] += b.m[1];	m[5] += b.m[5];	m[9]  += b.m[9] ;	m[13] += b.m[13];
	m[2] += b.m[2];	m[6] += b.m[6];	m[10] += b.m[10];	m[14] += b.m[14];
	m[3] += b.m[3];	m[7] += b.m[7];	m[11] += b.m[11];	m[15] += b.m[15];  
	
	return *this;
}   

rMatrix4& rMatrix4::operator -=(const rMatrix4& b){
	m[0] -= b.m[0];	m[4] -= b.m[4];	m[8]  -= b.m[8] ;	m[12] -= b.m[12];
	m[1] -= b.m[1];	m[5] -= b.m[5];	m[9]  -= b.m[9] ;	m[13] -= b.m[13];
	m[2] -= b.m[2];	m[6] -= b.m[6];	m[10] -= b.m[10];	m[14] -= b.m[14];
	m[3] -= b.m[3];	m[7] -= b.m[7];	m[11] -= b.m[11];	m[15] -= b.m[15];  
	
	return *this;
}   