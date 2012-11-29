#ifndef R_MATRIXUTIL_HPP
#define R_MATRIXUTIL_HPP

#include <cmath>

#include "rMath.hpp"
#include "rMatrix4.hpp"
#include "rVector3.hpp"

namespace rMatrixUtil{
	void LookAt(const rVector3& eye, const rVector3& target, const rVector3& up, rMatrix4& matrix);
	bool Perspective(float fovy, float aspect, float zNear, float zFar, rMatrix4& matrix);
	void Ortho2D(float left, float right, float bottom, float top, rMatrix4& matrix);
	void Ortho(float left, float right, float bottom, float top, float near, float far,rMatrix4& matrix);
};

#endif