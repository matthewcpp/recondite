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

rQuaternion::rQuaternion(const rVector3& axis, float degrees){
	SetFromAxisAngle(axis, degrees);
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


void rQuaternion::SetFromAxisAngle(float axisx, float axisy, float axisz, float degrees){
	float halfAngle = rMath::DegreeToRad(degrees) * 0.5f;
	float sin = std::sin(halfAngle);

	w = std::cos(halfAngle);
	x = sin * axisx;
	y = sin * axisy;
	z=  sin * axisz;
}

void rQuaternion::SetFromAxisAngle(const rVector3& axis, float degrees){
	SetFromAxisAngle(axis.x, axis.y, axis.z, degrees);
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

rQuaternion rQuaternion::Slerp(const rQuaternion& pStart , const rQuaternion& pEnd, float pFactor){
	{
		// calc cosine theta
		float cosom = pStart.x * pEnd.x + pStart.y * pEnd.y + pStart.z * pEnd.z + pStart.w * pEnd.w;

		// adjust signs (if necessary)
		rQuaternion end = pEnd;
		if (cosom < 0.0f)
		{
			cosom = -cosom;
			end.x = -end.x;   // Reverse all signs
			end.y = -end.y;
			end.z = -end.z;
			end.w = -end.w;
		}

		// Calculate coefficients
		float sclp, sclq;
		if (1.0f - cosom > 0.0001f) // 0.0001 -> some epsillon
		{
			// Standard case (slerp)
			float omega, sinom;
			omega = std::acos(cosom); // extract theta from dot product's cos theta
			sinom = std::sin(omega);
			sclp = std::sin((1.0f - pFactor) * omega) / sinom;
			sclq = std::sin(pFactor * omega) / sinom;
		}
		else
		{
			// Very close, do linear interp (because it's faster)
			sclp = 1.0f - pFactor;
			sclq = pFactor;
		}

		rQuaternion pOut;
		pOut.x = sclp * pStart.x + sclq * end.x;
		pOut.y = sclp * pStart.y + sclq * end.y;
		pOut.z = sclp * pStart.z + sclq * end.z;
		pOut.w = sclp * pStart.w + sclq * end.w;

		return pOut;
	}
}

bool rQuaternion::operator==(const rQuaternion& q) const{
	return x == q.x && y == q.y && z == q.z && w == q.w;
}

bool rQuaternion::operator!=(const rQuaternion& q) const{
	return !(*this == q);
}

const rQuaternion rQuaternion::Identity = rQuaternion(0,0,0,1);