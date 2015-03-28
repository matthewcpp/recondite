#ifndef R_MODELGEOMETRYDATA_HPP
#define R_MODELGEOMETRYDATA_HPP

#include "rBuild.hpp"
#include "data/rGeometryData.hpp"

class rModelGeometryData : public rGeometryData {
public:
	virtual void Clear() override;
	virtual void Allocate(size_t size);

	virtual void TransformVertex(size_t index, const rMatrix4& transform) override;
	virtual void PushVertex(const rVector3& position, const rVector3& normal) override;

	virtual size_t VertexCount() const override;
	virtual char* VertexData() const override;
	virtual size_t VertexDataSize() const override;

public:

	void SetVertex(size_t index, const rVector3& v, const rVector3& n, const rVector2& tc);
	void PushVertex(const rVector3& v, const rVector3& n, const rVector2& tc);
	void GetVertex(size_t index, rVector3* position, rVector2* texCoord, rVector3* normal) const;
	size_t VertexSizeInBytes() const;

private:

	struct rModelVertex{
		rModelVertex() {}
		rModelVertex(const rVector3& v, const rVector3& n, const rVector2& tc)
			:position(v), texCoord(tc), normal(n) {}

		rVector3 position;
		rVector2 texCoord;
		rVector3 normal;
	};

	typedef std::vector<rModelVertex> rModelVertexArray;

private:

	rModelVertexArray m_vertexData;
	rVertexBoneLinkMap m_vertexBoneLinks;
};

#endif