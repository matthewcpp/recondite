#ifndef R_GEOMETRYDATA_HPP
#define R_GEOMETRYDATA_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rVector2.hpp"
#include "rVector3.hpp"

class rGeometryData{
public:
	rGeometryData();
	
public:
	void SetVertexData(float* vertexData, size_t vertexCount, bool texCoords, bool normals);
	void SetFaceData(unsigned int* indicies, size_t indexCount);
	
	const float* GetVertexData() const;
	const unsigned short* GetIndexData() const;
	
	bool HasTextureCoords() const;
	bool HasNormals() const;
	
	void Clear();
	
	size_t VertexDataSize() const;
	size_t FaceIndexCount() const;
	
	size_t VertexSize() const;
	
private:
	rFloatArray m_vertexData;
	rIndexArray m_indexData;
	
	bool m_hasTextureCoords;
	bool m_hasNormals;
};

#endif
