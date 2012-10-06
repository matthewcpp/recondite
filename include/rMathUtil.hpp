#ifndef R_MATH_UTILS_HPP
#define R_MATH_UTILS_HPP

#include <algorithm>

#include "rMath.hpp"

#include "rTypes.hpp"
#include "rRectangle2.hpp"
#include "rCircle2.hpp"
#include "rMatrix3.hpp"
#include "rLine2.hpp"

#include "rVector3.hpp"

#include "rMatrix4.hpp"
#include "rQuaternion.hpp"

namespace rMath{
	float Max3(float n1 , float n2, float n3);

	void Matrix3TransformRectangle(const rMatrix3& m , rRectangle2& r);
	void Matrix3TransformCircle(const rMatrix3& m , rCircle2& c);

	rVector2 ClosestPointOnSegment(const rLineSegment2& ls , const rCircle2& c);

	void QuaterionToMatrix(const rQuaternion& q, rMatrix4& m);
	void SetTransformMatrix(const rVector3& translation, const rQuaternion& rotation, const rVector3& scale, rMatrix4& result);

	bool PointInBoundedXYPlane(const rVector3& corner1 , const rVector3& corner2 , const rVector3& point);
	bool PointInBoundedXZPlane(const rVector3& corner1 , const rVector3& corner2 , const rVector3& point);
	bool PointInBoundedYZPlane(const rVector3& corner1 , const rVector3& corner2 , const rVector3& point);
};

#endif