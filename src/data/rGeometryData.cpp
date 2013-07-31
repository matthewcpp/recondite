#include "data/rGeometryData.hpp"

rGeometryData::rGeometryData(){
	Clear();
}

void rGeometryData::SetVertexData(float* vertexData, size_t vertexCount, bool texCoords, bool normals){
	m_hasTextureCoords = texCoords;
	m_hasNormals = normals;
	size_t dataSize = VertexSize() * vertexCount;
	
	m_vertexData.resize(dataSize);
	memcpy(&m_vertexData[0], vertexData, dataSize);
}

const float* rGeometryData::GetVertexData() const{
	if (m_vertexData.size())
		return &m_vertexData[0];
	else
		return NULL;
}

size_t rGeometryData::VertexSize() const{
	size_t vertexSize = 3;
	
	if (m_hasTextureCoords)
		vertexSize += 2;
	
	if (m_hasNormals)
		vertexSize += 3;
	
	return vertexSize * sizeof(float);
}

size_t rGeometryData::VertexDataSize() const{
	return VertexCount() * VertexSize();
}


size_t rGeometryData::VertexCount() const{
	return m_vertexData.size();
}


void rGeometryData::SetElementData(unsigned short* elements, size_t elementCount){
	m_elementData.resize(elementCount);
	size_t dataSize = elementCount * sizeof(unsigned short);
	
	memcpy(&m_elementData[0], elements, dataSize);
}

size_t rGeometryData::ElementDataSize() const{
	ElementCount() * sizeof (unsigned short);
}

size_t rGeometryData::ElementCount() const{
	return m_elementData.size();
}

const unsigned short* rGeometryData::GetElementData() const{
	if (m_elementData.size())
		return &m_elementData[0];
	else
		return NULL;
}

bool rGeometryData::HasTextureCoords() const{
	return m_hasTextureCoords;
}

bool rGeometryData::HasNormals() const{
	return m_hasNormals;
}

void rGeometryData::Clear(){
	m_vertexData.clear();
	m_elementData.clear();
	m_path.clear();

	m_hasTextureCoords = false;
	m_hasNormals = false;
	m_error = rCONTENT_ERROR_NONE;
}

rString rGeometryData::Path() const{
	return m_path;
}

rContentError rGeometryData::GetError() const{
	return m_error;
}
