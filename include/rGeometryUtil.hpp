#ifndef R_GEOMETRYUTIL_HPP
#define R_GEOMETRYUTIL_HPP

#include "rDefs.hpp"
#include "rTypes.hpp"

#include "rRect.hpp"
#include "data/rGeometryData.hpp"

namespace rGeometryUtil{
	void CreateRectVerticies(const rRect rect, const rString& name, rGeometryData& geometry, bool texCoords);
};

#endif
