#ifndef R_PRIMITIVEGEOMETRY_HPP
#define R_PRIMITIVEGEOMETRY_HPP

#include <tuple>

#include "rBuild.hpp"

#include "asset/rModelData.hpp"
#include "rPrimitiveGeometryParams.hpp"

using namespace recondite;

namespace rPrimitiveGeometry{
	void RECONDITE_API CreateBox(const rPrimitiveBoxParams& params, ModelData& modelData);
	void RECONDITE_API CreateCone(const rPrimitiveConeParams& params, ModelData& modelData);
	void RECONDITE_API CreateCircle(const rPrimitiveCircleParams& params, ModelData& modelData);
	void RECONDITE_API CreateGrid(const rPrimitiveGridParams& params, ModelData& modelData);
	void RECONDITE_API CreateCylinder(const rPrimitiveCylinderParams& params, ModelData& modelData);
	void RECONDITE_API CreateSphere(const rPrimitiveSphereParams& params, ModelData& modelData);
}

#endif