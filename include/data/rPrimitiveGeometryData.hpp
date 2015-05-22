#ifndef R_PRIMITIVEGEOMETRYDATA_HPP
#define R_PRIMITIVEGEOMETRYDATA_HPP

#include <vector>

#include "rBuild.hpp"
#include "rGeometryData.hpp"

class RECONDITE_API rPrimitiveGeometryData : public rGeometryData{
public:

	virtual void TransformVertex(size_t index, const rMatrix4& transform) override;
	virtual void PushVertex(const rVector3& position, const rVector3& normal) override;
	virtual void GetVertex(size_t index, rVector3* position, rVector3* normal) const override;

	virtual size_t VertexCount() const override; 
	virtual char* VertexData() const override;
	virtual size_t VertexDataSize() const override;

	virtual rGeometryProfile GeometryProfile() const override;

private:
	struct rPrimitiveVertex {
		rPrimitiveVertex(){}
		rPrimitiveVertex(const rVector3& p, const rVector3& n)
			:position(p), normal(n){}

		rVector3 position;
		rVector3 normal;
	};

	typedef std::vector<rPrimitiveVertex> rPrimitiveVertexArray;

private:
	rPrimitiveVertexArray m_vertices;
};

#endif