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
	const float* GetVertexData() const;
	size_t VertexSize() const;
	size_t VertexDataSize() const;
	size_t VertexCount() const;
	
	void SetElementData(unsigned short* elements, size_t elementCount);
	const unsigned short* GetElementData() const;
	size_t ElementDataSize() const;
	size_t ElementCount() const;
	
	bool HasTextureCoords() const;
	bool HasNormals() const;
	
	void Clear();
	
	rString Path() const;
	rContentError GetError() const;
	
private:
	rFloatArray m_vertexData;
	rIndexArray m_elementData;
	
	bool m_hasTextureCoords;
	bool m_hasNormals;
	
	rString m_path;
	rContentError m_error;
};

#endif
