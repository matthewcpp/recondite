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
	rElementBufferData(unsigned short* elements, size_t elementCount);
	
public:
	
	void SetElementData(unsigned short* elements, size_t elementCount);
	
	const unsigned short* GetElementData() const;
	size_t ElementDataSize() const;
	size_t ElementCount() const;
	
	void Clear();
	
private:
	
	rIndexArray m_elementData;
};

typedef std::map<rString, rElementBufferData*> rElementBufferDataMap;

class rGeometryData{
public:
	rGeometryData();
	~rGeometryData();
	
public:
	void SetVertexData(float* vertexData, size_t vertexCount, bool texCoords, bool normals);
	const float* GetVertexData() const;
	size_t VertexSize() const;
	size_t VertexDataSize() const;
	size_t VertexCount() const;
	
	rElementBufferData* CreateElementBuffer(const rString& name);
	rElementBufferData* CreateElementBuffer(const rString& name, unsigned short* elements, size_t elementCount);
	
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
	
	
	bool m_hasTextureCoords;
	bool m_hasNormals;
	
	rString m_path;
	rContentError m_error;
};

#endif
