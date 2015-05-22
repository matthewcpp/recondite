#ifndef R_PRIMITIVEGEOMETRY_HPP
#define R_PRIMITIVEGEOMETRY_HPP

#include <tuple>

#include "rBuild.hpp"

#include "data/rGeometryData.hpp"
#include "rPrimitiveGeometryParams.hpp"

namespace rPrimitiveGeometry{
	void RECONDITE_API CreateBox(const rPrimitiveBoxParams& params, rGeometryData& data);
	void RECONDITE_API CreateCone(const rPrimitiveConeParams& params, rGeometryData& data);
	void RECONDITE_API CreateCircle(const rPrimitiveCircleParams& params, rGeometryData& data);
	void RECONDITE_API CreateGrid(const rPrimitiveGridParams& params, rGeometryData& data);
	void RECONDITE_API CreateCylinder(const rPrimitiveCylinderParams& params, rGeometryData& geometry);
	void RECONDITE_API CreateSphere(const rPrimitiveSphereParams& params, rGeometryData& geometry);
}

#endif