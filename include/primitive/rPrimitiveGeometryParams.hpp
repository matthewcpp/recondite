#ifndef R_PRIMITIVEGEOMETRYPARAMS_HPP
#define R_PRIMITIVEGEOMETRYPARAMS_HPP

#include "rBuild.hpp"

#include "rString.hpp"
#include "rVector3.hpp"

namespace rPrimitiveGeometry{
	struct RECONDITE_API rPrimitiveParams{
		rPrimitiveParams() 
			: createFaceMesh(true), faceMeshName("faces"), createWireMesh(true), wireMeshName("wire") {}

		bool createFaceMesh;
		rString faceMeshName;

		bool createWireMesh;
		rString wireMeshName;
	};

	struct RECONDITE_API rPrimitiveBoxParams : public rPrimitiveParams{
		rPrimitiveBoxParams() 
			: extents(rVector3::OneVector), widthSegments(1), heightSegments(1), depthSegments (1) {}
		rPrimitiveBoxParams(const rVector3& _extents, int _widthSegments, int _heightSegments, int _depthSegments) 
			: extents(_extents), widthSegments(_widthSegments), heightSegments(_heightSegments), depthSegments(_depthSegments) {}

		rVector3 extents;
		int widthSegments;
		int heightSegments;
		int depthSegments;
	};

	struct  RECONDITE_API rPrimitiveGridParams : public rPrimitiveParams{
	public:
		rPrimitiveGridParams()
			: width(1), depth(1), rows(1), columns(1) {}
		rPrimitiveGridParams(float _width, float _depth, size_t _rows, size_t _columns)
			: width(_width), depth(_depth), rows(_rows), columns(_columns) {}

		float width;
		float depth;

		size_t rows;
		size_t columns;
	};

	struct RECONDITE_API rPrimitiveConeParams : public rPrimitiveParams{
		rPrimitiveConeParams()
			:radius(1), height(1), segmentCount(20) {}
		rPrimitiveConeParams(float _radius, float _height, size_t _segmentCount)
			:radius(_radius), height(_height), segmentCount(_segmentCount) {}

		float radius;
		float height;

		size_t segmentCount;
	};

	struct RECONDITE_API rPrimitiveCylinderParams : public rPrimitiveParams{
		rPrimitiveCylinderParams()
			:radius(1.0f), height(1.0f), segmentCount(20) {}
		rPrimitiveCylinderParams(float _radius, float _height, size_t _segmentCount)
			:radius(_radius), height(_height), segmentCount(_segmentCount) {}

		float radius;
		float height;

		size_t segmentCount;
	};

	struct RECONDITE_API rPrimitiveCircleParams : public rPrimitiveParams{
		rPrimitiveCircleParams()
			: center(rVector3::ZeroVector), normal(rVector3::UpVector), radius(1.0f), segmentCount(15), start(0.0f), end(360.0f){}
		rPrimitiveCircleParams(const rVector3& _center, const rVector3& _normal, float _radius, size_t _segmentCount, float _start = 0.0f, float _end = 360.0f)
			: center(_center), normal(_normal), radius(_radius), segmentCount(_segmentCount), start(_start), end(_end) {}

		rVector3 center;
		rVector3 normal;
		float radius;
		size_t segmentCount;
		float start;
		float end;
	};

	struct RECONDITE_API rPrimitiveSphereParams : public rPrimitiveParams{
	public:
		rPrimitiveSphereParams()
			:radius(1.0f), rings(15), sectors(15) {}
		rPrimitiveSphereParams(float _radius, size_t _rings, size_t _sectors)
			:radius(_radius), rings(_rings), sectors(_sectors) {}

		float radius;
		size_t rings;
		size_t sectors;
	};

}


#endif