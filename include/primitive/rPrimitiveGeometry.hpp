#ifndef R_PRIMITIVEGEOMETRY_HPP
#define R_PRIMITIVEGEOMETRY_HPP

#include <tuple>

#include "rBuild.hpp"

#include "data/rGeometryData.hpp"

namespace rPrimitiveGeometry{
	void RECONDITE_API CreateBox(const rVector3& extents, std::tuple<int, int, int> segmentCounts, rGeometryData& geometry);
	void RECONDITE_API CreateGrid(const rVector3& extents, std::tuple<int, int> segmentCounts, rGeometryData& geometry);
	void RECONDITE_API CreateCircle(const rVector3& center, float radius, const rVector3& normal, size_t segmentCount, rGeometryData& geometry);
	void RECONDITE_API CreateCone(float radius, float height, size_t segmentCount, rGeometryData& geometry);
	void RECONDITE_API CreateCylinder(float radius, float height, size_t segmentCount, rGeometryData& geometry);
	void RECONDITE_API CreateSphere(float radius, size_t rings, size_t sectors, rGeometryData& geometry);
}

#endif