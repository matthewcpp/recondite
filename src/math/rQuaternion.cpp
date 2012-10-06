#include "rQuaternion.hpp"

rQuaternion::rQuaternion(const rVector3& eulerAngles){
	SetFromEulerAngles(eulerAngles.x , eulerAngles.y, eulerAngles.z);
}

rQuaternion::rQuaternion(float tx , float ty, float tz){
	SetFromEulerAngles(tx,ty,tz);
}

void rQuaternion::SetFromEulerAngles(const rVector3& angles){
	SetFromEulerAngles(angles.x , angles.y , angles.z);
}

void rQuaternion::SetFromEulerAngles(float tx , float ty, float tz){

	//convert to radian
	tz = rMath::DegreeToRad(tz)* 0.5f;
	ty = rMath::DegreeToRad(ty)* 0.5f;
	tx = rMath::DegreeToRad(tx)* 0.5f;

	//get half angles
	float cos_z_2 = std::cos(tz);
	float cos_y_2 = std::cos(ty);
	float cos_x_2 = std::cos(tx);

	float sin_z_2 = std::sin(tz);
	float sin_y_2 = std::sin(ty);
	float sin_x_2 = std::sin(tx);

	//assign quaternion members
	w = cos_z_2*cos_y_2*cos_x_2 + sin_z_2*sin_y_2*sin_x_2;
	x = cos_z_2*cos_y_2*sin_x_2 - sin_z_2*sin_y_2*cos_x_2;
	y = cos_z_2*sin_y_2*cos_x_2 + sin_z_2*cos_y_2*sin_x_2;
	z = sin_z_2*cos_y_2*cos_x_2 - cos_z_2*sin_y_2*sin_x_2;
}

void rQuaternion::TransformVector3(rVector3& v) const{
    rVector3 quatVec(x, y , z);
	rVector3 uv = quatVec.Cross(v);
	rVector3 uuv = quatVec.Cross(uv);

	uv *= (2.0f * w);
	uuv *= 2.0f;

	v= v + uv + uuv;
}

rVector3 rQuaternion::GetTransformedVector3(const rVector3& v) const{
	rVector3 returnVec = v;
	TransformVector3(returnVec);
	return returnVec;
}

float rQuaternion::Length() const{
	return std::sqrt(x*x + y*y + z*z + w*w);
}

float rQuaternion::LengthSquared() const{
	return x*x + y*y + z*z + w*w;
}

void rQuaternion::Normalize(){
	float l = Length();
	x /= l;
	y /= l;
	z /= l;
	w /= l;
}

//based on code from euclideanspace.com

rQuaternion rQuaternion::Slerp(const rQuaternion& q1 , const rQuaternion& q2, float t){
	rQuaternion qr;
	// Calculate angle between them.
	float cosHalfTheta = q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
	// if q1=q2 or q1=-q2 then theta = 0 and we can return q1
	if (std::abs(cosHalfTheta) >= 1.0f){
		qr = q1;
		return qr;
	}

	float halfTheta = acos(cosHalfTheta);
	float sinHalfTheta = sqrt(1.0f - cosHalfTheta*cosHalfTheta);

	// if theta = 180 degrees then result is not fully defined
	// we could rotate around any axis normal to q1 or q2
	if (std::fabs(sinHalfTheta) < 0.001f){ 
		qr.w = q1.w * 0.5f + q2.w * 0.5f;
		qr.x = q1.x * 0.5f + q2.x * 0.5f;
		qr.y = q1.y * 0.5f + q2.y * 0.5f;
		qr.z = q1.z * 0.5f + q2.z * 0.5f;
		return qr;
	}

	float ratioA = sin((1.0f - t) * halfTheta) / sinHalfTheta;
	float ratioB = sin(t * halfTheta) / sinHalfTheta; 

	qr.w = q1.w * ratioA + q2.w * ratioB;
	qr.x = q1.x * ratioA + q2.x * ratioB;
	qr.y = q1.y * ratioA + q2.y * ratioB;
	qr.z = q1.z * ratioA + q2.z * ratioB;
	return qr;
}