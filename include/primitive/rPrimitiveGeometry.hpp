#ifndef R_PRIMITIVEGEOMETRY_HPP
#define R_PRIMITIVEGEOMETRY_HPP

#include <tuple>

#include "data/rGeometryData.hpp"

namespace rPrimitiveGeometry{
	void CreateBox(const rVector3& extents, std::tuple<int,int,int> segmentCounts, rGeometryData& geometry);
}

#endif