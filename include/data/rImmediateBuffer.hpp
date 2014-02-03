#ifndef R_GEOMETRYBUFFER_HPP
#define R_GEOMETRYBUFFER_HPP

#include <map>
#include <fstream>
#include <cstring>
#include <utility>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rVector2.hpp"
#include "rVector3.hpp"
#include "rMatrix4.hpp"

class rImmediateBuffer {
public:
	rImmediateBuffer();
	rImmediateBuffer(rGeometryType geometryType, size_t vertexSize, bool texCoords);

	void Allocate(size_t count);
	void TransformVertex(size_t i, const rMatrix4& matrix);

	void SetVertex(size_t index, const rVector2& position);
	void SetVertex(size_t index, const rVector2& position, const rVector2& texCoord);
	void SetVertex(size_t index, float x, float y);
	void SetVertex(size_t index, float x, float y, float u, float v);

	void SetVertex(size_t index, const rVector3& position);
	void SetVertex(size_t index, const rVector3& position, const rVector2& texCoord);
	void SetVertex(size_t index, float x, float y, float z);
	void SetVertex(size_t index, float x, float y, float z, float u, float v);
		 
	void SetIndex(size_t index, unsigned short v1, unsigned int v2);
	void SetIndex(size_t index, unsigned short v1, unsigned int v2, unsigned int v3);

	void PushVertex(const rVector2& position);
	void PushVertex(const rVector2& position, const rVector2& texCoord);
	void PushVertex(float x, float y);
	void PushVertex(float x, float y, float u, float v);

	void PushVertex(const rVector3& position);
	void PushVertex(const rVector3& position, const rVector2& texCoord);
	void PushVertex(float x, float y, float z);
	void PushVertex(float x, float y, float z, float u, float v);

	void PushIndex(unsigned short v1);
	void PushIndex(unsigned short v1, unsigned int v2);
	void PushIndex(unsigned short v1, unsigned int v2, unsigned int v3);

	void SetIndexBuffer(const unsigned short* indices, size_t indexCount);

	void Reset(rGeometryType geometryType, size_t vertexSize, bool texCoords);

private:
	size_t VertexDataArrayIndex(size_t index) const;

public:

	bool HasTexCoords() const;
	size_t VertexSize() const;
	size_t VertexCount() const;

	char* VertexData() const;
	size_t VertexDataSize() const;

	char* IndexData() const;
	size_t IndexCount() const;
	size_t IndexDataSize() const;

	rGeometryType GeometryType() const;

private:
	rFloatArray m_vertexData;
	rIndexArray m_indexData;

	size_t m_vertexSize;
	bool m_texCoords;
	rGeometryType m_geometryType;
};

#endif