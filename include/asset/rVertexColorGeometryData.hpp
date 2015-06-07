#ifndef R_VERTEXCOLORGEOMETRYDATA_HPP
#define R_VERTEXCOLORGEOMETRYDATA_HPP

#include <vector>

#include "rBuild.hpp"
#include "rGeometryData.hpp"

#include "rVector4.hpp"
#include "rColor.hpp"

class RECONDITE_API rVertexColorGeometryData : public rGeometryData{
public:
	virtual void TransformVertex(size_t index, const rMatrix4& transform) override;
	virtual void PushVertex(const rVector3& position, const rVector3& normal) override;
	virtual void GetVertex(size_t index, rVector3* position, rVector3* normal) const override;

	virtual size_t VertexCount() const override;
	virtual char* VertexData() const override;
	virtual size_t VertexDataSize() const override;

	virtual rGeometryProfile GeometryProfile() const override;

	virtual void Clear();

public:
	void PushVertex(const rVector3& position, const rVector3& normal, const rColor& color);

	void SetColorForVertices(size_t startingIndex, const rColor& color);
	void SetColorForVertices(size_t startingIndex, size_t endingIndex, const rColor& color);

private:
	struct rVertexColorVertex {
		rVertexColorVertex(){}
		rVertexColorVertex(const rVector3& p, const rVector3& n, const rVector4& c)
			:position(p), normal(n), color(c){}

		rVector3 position;
		rVector3 normal;
		rVector4 color;
	};

private:
	std::vector<rVertexColorVertex> m_vertices;
};

#endif