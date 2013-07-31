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

void rGeometryData::SetFaceData(unsigned int* indicies, size_t indexCount){
	m_indexData.resize(indexCount);
	
	memcpy(&m_indexData[0], indicies, indexCount);
}

const float* rGeometryData::GetVertexData() const{
	if (m_vertexData.size())
		return NULL;
	else
		return &m_vertexData[0];
}

const unsigned short* rGeometryData::GetIndexData() const{
	if (m_indexData.size())
		return NULL;
	else
		return &m_indexData[0];
}

bool rGeometryData::HasTextureCoords() const{
	return m_hasTextureCoords;
}

bool rGeometryData::HasNormals() const{
	return m_hasNormals;
}

void rGeometryData::Clear(){
	m_vertexData.clear();
	m_indexData.clear();
	
	m_hasTextureCoords = false;
	m_hasNormals = false;
}

size_t rGeometryData::VertexDataSize() const{
	return m_vertexData.size();
}

size_t rGeometryData::FaceIndexCount() const{
	return m_indexData.size();
}

size_t rGeometryData::VertexSize() const{
	size_t vertexSize = 3;
	
	if (m_hasTextureCoords)
		vertexSize += 2;
	
	if (m_hasNormals)
		vertexSize += 3;
	
	return vertexSize;
}
