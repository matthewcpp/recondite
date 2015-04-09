#ifndef R_PRIMITIVEGEOMETRY_HPP
#define R_PRIMITIVEGEOMETRY_HPP

#include <tuple>

#include "data/rGeometryData.hpp"

namespace rPrimitiveGeometry{
	void CreateBox(const rVector3& extents, std::tuple<int, int, int> segmentCounts, rGeometryData& geometry);
	void CreateGrid(const rVector3& extents, std::tuple<int, int> segmentCounts, rGeometryData& geometry);
	void CreateCircle(const rVector3& center, float radius, const rVector3& normal, size_t segmentCount, rGeometryData& geometry);
	void CreateCone(float radius, float height, size_t segmentCount, rGeometryData& geometry);
	void CreateCylinder(float radius, float height, size_t segmentCount, rGeometryData& geometry);
	void CreateSphere(float radius, size_t rings, size_t sectors, rGeometryData& geometry);
}

#endif