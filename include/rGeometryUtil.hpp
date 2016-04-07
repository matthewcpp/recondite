#ifndef R_GEOMETRYUTIL_HPP
#define R_GEOMETRYUTIL_HPP

#include <cmath>

#include "rDefs.hpp"
#include "rTypes.hpp"

#include "rRect.hpp"
#include "rAlignedBox3.hpp"

#include "data/rImmediateBuffer.hpp"
#include "asset/rTexCoordGeometryData.hpp"

#include "asset/rFont.hpp"
#include "rSkeleton.hpp"

#include "rMathUtil.hpp"
#include "rCircle2.hpp"

namespace rGeometryUtil{
	bool CreateRoundedRectVerticies(const rRect& rect, float radius, int detail, rImmediateBuffer& geometry, float zValue = 0.0f);
	bool CreateRectVerticies(const rRect& rect, rImmediateBuffer& geometry, bool texCoords, float zValue = 0.0f);
	bool CreateWireRectVerticies(const rRect& rect, rImmediateBuffer& geometry, float zValue = 0.0f);
	bool CreateCircleVerticies(const rCircle2& circle, size_t segments, rImmediateBuffer& geometry, float zValue = 0.0f);

	void CreateWireAlignedBoxVerticies(const rAlignedBox3& box, rImmediateBuffer& geometry);
	void Create2DText(const rString& str, const rFont* font, const rRect& bounding, rImmediateBuffer& geometry);
	void CreateSkeletonGeometry(const rSkeleton* skeleton, rImmediateBuffer& geometryData, rImmediateBuffer& lineData);

	void CreateCircle3d(rTexCoordGeometryData& geometry, const rVector3& center, float radius, const rVector3& normal, size_t segmentCount);
	void GeneratePrimitiveCone(float baseRadius, float height, size_t segmentCount, const rString& name, rTexCoordGeometryData& geometry);
};

#endif
