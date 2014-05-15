#ifndef R_MATRIXUTIL_HPP
#define R_MATRIXUTIL_HPP

#include <cmath>

#include "rBuild.hpp"

#include "rMathUtil.hpp"
#include "rMatrix4.hpp"
#include "rVector3.hpp"
#include "rVector4.hpp"
#include "rRect.hpp"

#include "rQuaternion.hpp"

namespace rMatrixUtil{
	void RECONDITE_API LookAt(const rVector3& eye, const rVector3& target, const rVector3& up, rMatrix4& matrix);
	bool RECONDITE_API Perspective(float fovy, float aspect, float zNear, float zFar, rMatrix4& matrix);
	void RECONDITE_API Ortho2D(float left, float right, float bottom, float top, rMatrix4& matrix);
	void RECONDITE_API Ortho(float left, float right, float bottom, float top, float near, float far,rMatrix4& matrix);
	bool RECONDITE_API Unproject(const rVector3& point, const rMatrix4& modelMatrix, const rMatrix4& projectionMatrix, const rRect& viewport, rVector3& out);

	void RECONDITE_API QuaterionToMatrix(const rQuaternion& q, rMatrix4& m);
};

#endif