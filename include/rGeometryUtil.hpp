#ifndef R_GEOMETRYUTIL_HPP
#define R_GEOMETRYUTIL_HPP

#include <cmath>

#include "rDefs.hpp"
#include "rTypes.hpp"

#include "rRect.hpp"
#include "rAlignedBox3.hpp"

#include "data/rGeometryData.hpp"

#include "rMathUtil.hpp"

namespace rGeometryUtil{
	void CreateRectVerticies(const rRect& rect, const rString& name, rGeometryData& geometry, bool texCoords);
	void CreateCircleVerticies(const rCircle2& circle, size_t segments, const rString& name, rGeometryData& geometry);

	void CreateWireAlignedBoxVerticies(const rAlignedBox3& box, const rString& name, rGeometryData& geometry);
};

#endif
