#ifndef R_GEOMETRYDATA_HPP
#define R_GEOMETRYDATA_HPP

#include <map>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rVector2.hpp"
#include "rVector3.hpp"

class rElementBufferData{
public:
	rElementBufferData();
	rElementBufferData(unsigned short* elements, size_t elementCount, rGeometryType type);
	
public:
	
	void SetElementData(unsigned short* elements, size_t elementCount, rGeometryType type);
	
	const unsigned short* GetElementData() const;
	size_t ElementDataSize() const;
	size_t ElementCount() const;
	
	void Push(unsigned short v1, unsigned short v2, unsigned short v3);
	
	void Clear();
	
	rGeometryType GeometryType() const;
	void SetGeometryType(rGeometryType type);

private:
	
	rIndexArray m_elementData;
	rGeometryType m_geometryType;
};

typedef std::map<rString, rElementBufferData*> rElementBufferDataMap;

class rGeometryData{
public:
	rGeometryData();
	~rGeometryData();
	
public:
	void SetVertexData(float* vertexData, size_t vertexElementSize, size_t vertexCount, bool texCoords, bool normals);
	size_t Allocate(size_t vertexElementSize, size_t vertexCount, bool texCoords, bool normals);
	
	const float* GetVertexData() const;
	size_t VertexElementSize() const;
	size_t VertexSizeInBytes() const;
	size_t VertexDataSizeInBytes() const;
	size_t VertexDataCount() const;
	
	rElementBufferData* CreateElementBuffer(const rString& name);
	rElementBufferData* CreateElementBuffer(const rString& name, unsigned short* elements, size_t elementCount, rGeometryType type);
	
	void SetVertex(size_t index, float x, float y);
	void SetVertex(size_t index, const rVector2& v);
	void SetVertex(size_t index, float x, float y, float u, float v);
	void SetVertex(size_t index, const rVector3& v, const rVector2& tc, const rVector3& n);
	void SetVertex(size_t index, const rVector3& v, const rVector2& tc);
	
	size_t ElementBufferCount() const;
	bool RemoveElementBuffer(const rString& name);
	rElementBufferData* GetElementBuffer(const rString& name) const;
	void GetElementBufferNames(rArrayString& names) const;
	
	bool HasTextureCoords() const;
	bool HasNormals() const;
	
	void Clear();
	
	rString Path() const;
	rContentError GetError() const;
	
private:
	rFloatArray m_vertexData;
	rElementBufferDataMap m_elementBuffers;
	
	size_t m_vertexElementSize;
	
	bool m_hasTextureCoords;
	bool m_hasNormals;
	
	rString m_path;
	rContentError m_error;
};

#endif
