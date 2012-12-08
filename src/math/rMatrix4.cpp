#include "rMatrix4.hpp"

const rMatrix4 rMatrix4::IdentityMatrix = rMatrix4();

rMatrix4::rMatrix4(){
	LoadIdentity();
}

rMatrix4::rMatrix4(const rMatrix4& matrix){
	memcpy(m, matrix.m, sizeof(float) * 16);
}

rMatrix4::rMatrix4(float* data){
	memcpy(m, data, sizeof(float) * 16);
}

void rMatrix4::LoadIdentity(){
	memset(this , 0 , sizeof(rMatrix4) );
	SetUniformScale(1.0f);
}

void rMatrix4::SetUniformScale(float k){
	m[0] = k;
	m[5] = k;
	m[10] = k;
	m[15] = k;
}

void rMatrix4::SetScale(const rVector3& s){
	m[0] = s.x;
	m[5] = s.y;
	m[10] = s.z;
	m[15] = 1.0f;
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

rVector4 rMatrix4::GetTransformedVector4(const rVector4& v) const{
	rVector4 r = v;
	TransformVector4(r);
	return r;
}

void rMatrix4::TransformVector4(rVector4& v)const{
	rVector4 r;
	r.x = m[0] * v.x + m[4] * v.y + m[8] * v.z + m[12] * v.w;
	r.y = m[1] * v.x + m[5] * v.y + m[9] * v.z + m[13] * v.w;
	r.z = m[2] * v.x + m[6] * v.y + m[10] * v.z + m[14] * v.w;
	r.w = m[3] * v.x + m[7] * v.y + m[11] * v.z + m[15] * v.w;
	v = r;
}

bool rMatrix4::Invert(){
    float inv[16];
    float det;
    int i;

    inv[0] =   m[5]*m[10]*m[15] - m[5]*m[11]*m[14] - m[9]*m[6]*m[15]
             + m[9]*m[7]*m[14] + m[13]*m[6]*m[11] - m[13]*m[7]*m[10];
    inv[4] =  -m[4]*m[10]*m[15] + m[4]*m[11]*m[14] + m[8]*m[6]*m[15]
             - m[8]*m[7]*m[14] - m[12]*m[6]*m[11] + m[12]*m[7]*m[10];
    inv[8] =   m[4]*m[9]*m[15] - m[4]*m[11]*m[13] - m[8]*m[5]*m[15]
             + m[8]*m[7]*m[13] + m[12]*m[5]*m[11] - m[12]*m[7]*m[9];
    inv[12] = -m[4]*m[9]*m[14] + m[4]*m[10]*m[13] + m[8]*m[5]*m[14]
             - m[8]*m[6]*m[13] - m[12]*m[5]*m[10] + m[12]*m[6]*m[9];
    inv[1] =  -m[1]*m[10]*m[15] + m[1]*m[11]*m[14] + m[9]*m[2]*m[15]
             - m[9]*m[3]*m[14] - m[13]*m[2]*m[11] + m[13]*m[3]*m[10];
    inv[5] =   m[0]*m[10]*m[15] - m[0]*m[11]*m[14] - m[8]*m[2]*m[15]
             + m[8]*m[3]*m[14] + m[12]*m[2]*m[11] - m[12]*m[3]*m[10];
    inv[9] =  -m[0]*m[9]*m[15] + m[0]*m[11]*m[13] + m[8]*m[1]*m[15]
             - m[8]*m[3]*m[13] - m[12]*m[1]*m[11] + m[12]*m[3]*m[9];
    inv[13] =  m[0]*m[9]*m[14] - m[0]*m[10]*m[13] - m[8]*m[1]*m[14]
             + m[8]*m[2]*m[13] + m[12]*m[1]*m[10] - m[12]*m[2]*m[9];
    inv[2] =   m[1]*m[6]*m[15] - m[1]*m[7]*m[14] - m[5]*m[2]*m[15]
             + m[5]*m[3]*m[14] + m[13]*m[2]*m[7] - m[13]*m[3]*m[6];
    inv[6] =  -m[0]*m[6]*m[15] + m[0]*m[7]*m[14] + m[4]*m[2]*m[15]
             - m[4]*m[3]*m[14] - m[12]*m[2]*m[7] + m[12]*m[3]*m[6];
    inv[10] =  m[0]*m[5]*m[15] - m[0]*m[7]*m[13] - m[4]*m[1]*m[15]
             + m[4]*m[3]*m[13] + m[12]*m[1]*m[7] - m[12]*m[3]*m[5];
    inv[14] = -m[0]*m[5]*m[14] + m[0]*m[6]*m[13] + m[4]*m[1]*m[14]
             - m[4]*m[2]*m[13] - m[12]*m[1]*m[6] + m[12]*m[2]*m[5];
    inv[3] =  -m[1]*m[6]*m[11] + m[1]*m[7]*m[10] + m[5]*m[2]*m[11]
             - m[5]*m[3]*m[10] - m[9]*m[2]*m[7] + m[9]*m[3]*m[6];
    inv[7] =   m[0]*m[6]*m[11] - m[0]*m[7]*m[10] - m[4]*m[2]*m[11]
             + m[4]*m[3]*m[10] + m[8]*m[2]*m[7] - m[8]*m[3]*m[6];
    inv[11] = -m[0]*m[5]*m[11] + m[0]*m[7]*m[9] + m[4]*m[1]*m[11]
             - m[4]*m[3]*m[9] - m[8]*m[1]*m[7] + m[8]*m[3]*m[5];
    inv[15] =  m[0]*m[5]*m[10] - m[0]*m[6]*m[9] - m[4]*m[1]*m[10]
             + m[4]*m[2]*m[9] + m[8]*m[1]*m[6] - m[8]*m[2]*m[5];

    det = m[0]*inv[0] + m[1]*inv[4] + m[2]*inv[8] + m[3]*inv[12];
    if (det == 0)
        return false;

    det = 1.0f / det;

    for (i = 0; i < 16; i++)
        m[i] = inv[i] * det;

    return true;
}

bool rMatrix4::GetInvertedMatrix(rMatrix4& m) const{
	m = *this;
	return m.Invert();
}

rMatrix4& rMatrix4::operator *=(float k){
	for (size_t i = 0; i < 16; i++)
		m[i] *= k;     

	return *this;                                          
}     

rMatrix4 rMatrix4::operator *(float k){
	rMatrix4 r;

	for (size_t i = 0; i < 16; i++)
		r.m[i] = m[i] * k;

	return r;
}
                  
rMatrix4& rMatrix4::operator +=(const rMatrix4& b){
	for (size_t i = 0; i < 16; i++)
		m[i] += b.m[i];
	
	return *this;
}

rMatrix4 rMatrix4::operator +(const rMatrix4& b) const{
	rMatrix4 result;

	for (size_t i = 0; i < 16; i++)
		result.m[i] = m[i] + b.m[i];

	return result;
}   

rMatrix4& rMatrix4::operator -=(const rMatrix4& b){
	for (size_t i = 0; i < 16; i++)
		m[i] -= b.m[i];

	return *this;
}

rMatrix4 rMatrix4::operator -(const rMatrix4& b) const{
	rMatrix4 result;

	for (size_t i = 0; i < 16; i++)
		result.m[i] = m[i] - b.m[i];

	return result;
}   

rMatrix4 rMatrix4::operator *(const rMatrix4& b) const{
	rMatrix4 r;
/*
	r.m[ 0] = m[0] * b.m[0] + m[4] * b.m[1] + m[8] * b.m[2] + m[12] * b.m[3];
	r.m[ 1] = m[1] * b.m[0] + m[5] * b.m[1] + m[9] * b.m[2] + m[13] * b.m[3];
	r.m[ 2] = m[2] * b.m[0] + m[6] * b.m[1] + m[10] * b.m[2] + m[14] * b.m[3];
	r.m[ 3] = m[3] * b.m[0] + m[7] * b.m[1] + m[11] * b.m[2] + m[15] * b.m[3];

	r.m[ 4] = m[0] * b.m[4] + m[4] * b.m[5] + m[8] * b.m[6] + m[12] * b.m[7];
	r.m[ 5] = m[1] * b.m[4] + m[5] * b.m[5] + m[9] * b.m[6] + m[13] * b.m[7];
	r.m[ 6] = m[2] * b.m[4] + m[6] * b.m[5] + m[10] * b.m[6] + m[14] * b.m[7];
	r.m[ 7] = m[3] * b.m[4] + m[7] * b.m[5] + m[11] * b.m[6] + m[15] * b.m[7];

	r.m[ 8] = m[0] * b.m[8] + m[4] * b.m[9] + m[8] * b.m[10] + m[12] * b.m[11];
	r.m[ 9] = m[1] * b.m[8] + m[5] * b.m[9] + m[9] * b.m[10] + m[13] * b.m[11];
	r.m[10] = m[2] * b.m[8] + m[6] * b.m[9] + m[10] * b.m[10] + m[14] * b.m[11];
	r.m[11] = m[3] * b.m[8] + m[7] * b.m[9] + m[11] * b.m[10] + m[15] * b.m[11];

	r.m[12] = m[0] * b.m[12] + m[4] * b.m[13] + m[8] * b.m[14] + m[12] * b.m[15];
	r.m[13] = m[1] * b.m[12] + m[5] * b.m[13] + m[9] * b.m[14] + m[13] * b.m[15];
	r.m[14] = m[2] * b.m[12] + m[6] * b.m[13] + m[10] * b.m[14] + m[14] * b.m[15];
	r.m[15] = m[3] * b.m[12] + m[7] * b.m[13] + m[11] * b.m[14] + m[15] * b.m[15];
	*/
	
	    int i, j;

    for (i = 0; i < 4; i++) {
	for (j = 0; j < 4; j++) {
	    r[i*4+j] = 
		m[i*4+0]*b.m[0*4+j] +
		m[i*4+1]*b.m[1*4+j] +
		m[i*4+2]*b.m[2*4+j] +
		m[i*4+3]*b.m[3*4+j];
	}
    }

	return r;
}

rMatrix4& rMatrix4::operator *=(const rMatrix4& b){
	*this = *this * b;
	return *this;
}