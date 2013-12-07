#ifndef R_GEOMETRYUTIL_HPP
#define R_GEOMETRYUTIL_HPP

#include <cmath>

#include "rDefs.hpp"
#include "rTypes.hpp"

#include "rRect.hpp"
#include "rAlignedBox3.hpp"

#include "data/rGeometryData.hpp"

#include "rFont.hpp"
#include "rSkeleton.hpp"

#include "rMathUtil.hpp"

namespace rGeometryUtil{
	void CreateRectVerticies(const rRect& rect, const rString& name, rGeometryData& geometry, bool texCoords);
	void CreateWireRectVerticies(const rRect& rect, const rString& name, rGeometryData& geometry);
	void CreateCircleVerticies(const rCircle2& circle, size_t segments, const rString& name, rGeometryData& geometry);

	void CreateWireAlignedBoxVerticies(const rAlignedBox3& box, const rString& name, rGeometryData& geometry);
	void Create2DText(const rString& str, const rFont* font, const rRect& bounding, const rString& name, rGeometryData& geometry);
	void CreateSkeletonGeometry(const rSkeleton* skeleton, const rString& name, rGeometryData& geometryData);
};

#endif
