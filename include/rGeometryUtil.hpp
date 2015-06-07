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
	void CreateRoundedRectVerticies(const rRect& rect, float radius, int detail, rImmediateBuffer& geometry);
	void CreateRectVerticies(const rRect& rect, rImmediateBuffer& geometry, bool texCoords);
	void CreateWireRectVerticies(const rRect& rect, rImmediateBuffer& geometry);
	void CreateCircleVerticies(const rCircle2& circle, size_t segments, rImmediateBuffer& geometry);

	void CreateWireAlignedBoxVerticies(const rAlignedBox3& box, rImmediateBuffer& geometry);
	void Create2DText(const rString& str, const rFont* font, const rRect& bounding, rImmediateBuffer& geometry);
	void CreateSkeletonGeometry(const rSkeleton* skeleton, rImmediateBuffer& geometryData, rImmediateBuffer& lineData);

	void CreateCircle3d(rTexCoordGeometryData& geometry, const rVector3& center, float radius, const rVector3& normal, size_t segmentCount);
	void GeneratePrimitiveCone(float baseRadius, float height, size_t segmentCount, const rString& name, rTexCoordGeometryData& geometry);
};

#endif
