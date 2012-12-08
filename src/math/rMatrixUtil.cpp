#include "rMatrixUtil.hpp"

void rMatrixUtil::LookAt(const rVector3& eye, const rVector3& target, const rVector3& up, rMatrix4& matrix){
	matrix.LoadIdentity();
	rVector3 forward, side, upv;
	
	forward = target - eye;
	
	forward.Normalize();
	
	upv = up;
	side = forward.Cross(upv);
	side.Normalize();
	
	upv = side.Cross(forward);
	
	matrix.m[0] = side.x;
	matrix.m[4] = side.y;
	matrix.m[8] = side.z;
	
	matrix.m[1] = upv.x;
	matrix.m[5] = upv.y;
	matrix.m[9] = upv.z;
	
	matrix.m[2] = -forward.x;
	matrix.m[6] = -forward.y;
	matrix.m[10] = -forward.z;

	rMatrix4 t;
	t.SetTranslate(-eye);

	matrix *= t;
}

bool rMatrixUtil::Perspective(float fovy, float aspect, float zNear, float zFar, rMatrix4& matrix){
	float sine, cotangent, deltaZ;
	float radians = rMath::DegreeToRad(fovy / 2.0f);
	deltaZ = zFar - zNear;
	sine = std::sin(radians);
	
	if (deltaZ == 0 || sine == 0 || aspect == 0) 
		return false;
  
	cotangent = std::cos(radians) / sine;
	matrix.LoadIdentity();
	matrix.m[0] = cotangent / aspect;
	matrix.m[5] = cotangent;
	matrix.m[10] = -(zFar + zNear) / deltaZ;
	matrix.m[11] = -1;
	matrix.m[15] = -2 * zNear * zFar / deltaZ;
	matrix.m[16] = 0;
}

void rMatrixUtil::Ortho2D(float left, float right, float bottom, float top, rMatrix4& matrix){
	rMatrixUtil::Ortho(left,right,bottom,top, -1.0f , 1.0f, matrix);
}

void rMatrixUtil::Ortho(float left, float right, float bottom, float top, float near, float far,rMatrix4& matrix){
	matrix.m[0] = 2.0f / (right - left);
	matrix.m[4] = 0.0f;
	matrix.m[8] = 0.0f;
	matrix.m[12] = -(right + left) / (right - left);
	
	matrix.m[1] = 0.0f;
	matrix.m[5] = 2.0f / (top - bottom);
	matrix.m[9] = 0.0f;
	matrix.m[13] = -(top + bottom) / (top - bottom);
	
	matrix.m[2] = 0.0f;
	matrix.m[6] = 0.0f;
	matrix.m[10] = -2.0f / (far - near);
	matrix.m[14] = -(far + near) / (far - near);
	
	matrix.m[3] = 0.0f;
	matrix.m[7] = 0.0f;
	matrix.m[11] = 0.0f;
	matrix.m[15] = 1.0f;
}

bool rMatrixUtil::Unproject(const rVector3& point, const rMatrix4& modelMatrix, const rMatrix4& projectionMatrix, const rRect& viewport, rVector3& out){
	rMatrix4 finalMatrix = modelMatrix * projectionMatrix;
	
	if (!finalMatrix.Invert())
		return false;
	
	rVector4 in (point.x,point.y,point.z, 1.0f);

	/* Map x and y from window coordinates */
	in.x = (in.x - viewport.x) / viewport.width;
	in.y = (in.y - viewport.y) / viewport.height;
	
	/* Map to range -1 to 1 */
	in.x = in.x * 2.0f - 1.0f;
	in.y = in.y * 2.0f - 1.0f;
	in.z = in.z * 2.0f - 1.0f;
	
	rVector4 ret = finalMatrix.GetTransformedVector4(in);
	
	if (ret.w == 0.0f)
		return false;
	
	ret /= ret.w;
	out.x = ret.x;
	out.y = ret.y;
	out.z = ret.z;
	
	return true;
}