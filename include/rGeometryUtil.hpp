#ifndef R_GEOMETRYUTIL_HPP
#define R_GEOMETRYUTIL_HPP

#include <cmath>

#include "rDefs.hpp"
#include "rTypes.hpp"

#include "rRect.hpp"
#include "rAlignedBox3.hpp"

#include "data/rImmediateBuffer.hpp"

#include "asset/rFont.hpp"
#include "rSkeleton.hpp"

#include "rMathUtil.hpp"
#include "rCircle2.hpp"

namespace rGeometryUtil{
	bool CreateRoundedRectVerticies(const rRect& rect, float radius, int detail, rImmediateBuffer& geometry, float zValue = 0.0f);
	bool CreateRoundedWireRectVerticies(const rRect& rect, float radius, int detail, rImmediateBuffer& geometry, float zValue = 0.0f);
	bool CreateRectVerticies(const rRect& rect, rImmediateBuffer& geometry, bool texCoords, float zValue = 0.0f);
	bool CreateWireRectVerticies(const rRect& rect, rImmediateBuffer& geometry, float zValue = 0.0f);
	bool CreateCircleVerticies(const rCircle2& circle, size_t segments, rImmediateBuffer& geometry, float zValue = 0.0f);

	void CreateWireAlignedBoxVerticies(const rAlignedBox3& box, rImmediateBuffer& geometry);
};

#endif
