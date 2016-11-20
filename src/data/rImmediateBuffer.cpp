#include "data/rImmediateBuffer.hpp"

rImmediateBuffer::rImmediateBuffer(){
	Reset(rGeometryType::Lines, 3, false);
}

rImmediateBuffer::rImmediateBuffer(rGeometryType geometryType, size_t vertexSize, bool texCoords){
	Reset(geometryType, vertexSize, texCoords);
}

void rImmediateBuffer::Reset(rGeometryType geometryType, size_t vertexSize, bool texCoords){
	m_geometryType = geometryType;
	m_vertexSize = vertexSize;
	m_texCoords = texCoords;

	Clear();
}

void rImmediateBuffer::Clear() {
	m_vertexData.clear();
	m_indexData.clear();
}

bool rImmediateBuffer::HasTexCoords() const{
	return m_texCoords;
}

size_t rImmediateBuffer::VertexSize() const{
	return m_vertexSize;
}

size_t rImmediateBuffer::VertexCount() const{
	size_t size = m_texCoords ? m_vertexSize + 2 : m_vertexSize;
	return m_vertexData.size() / size;
}

void rImmediateBuffer::Allocate(size_t count){
	size_t size = m_texCoords ? m_vertexSize + 2 : m_vertexSize;
	m_vertexData.resize(size * count);
}

char* rImmediateBuffer::VertexData() const{
	if (m_vertexData.size() == 0){
		return NULL;
	}
	else{
		return (char*)&m_vertexData[0];
	}
}

size_t rImmediateBuffer::VertexDataSize() const{
	return m_vertexData.size() * sizeof(rFloatArray::value_type);
}

	void rImmediateBuffer::SetIndex(size_t index, unsigned short v1, unsigned int v2){
	size_t i = index * 2;

	m_indexData[i] = v1;
	m_indexData[i + 1] = v2;
}

void rImmediateBuffer::SetIndex(size_t index, unsigned short v1, unsigned int v2, unsigned int v3){
	size_t i = index * 3;

	m_indexData[i] = v1;
	m_indexData[i + 1] = v2;
	m_indexData[i + 2] = v3;
}


void rImmediateBuffer::SetVertex(size_t index, const rVector2& position){
	size_t i = index * 2;

	m_vertexData[i] = position.x;
	m_vertexData[i + 1] = position.y;
}

void rImmediateBuffer::SetVertex(size_t index, const rVector2& position, const rVector2& texCoord){
	size_t i = index * 4;

	m_vertexData[i] = position.x;
	m_vertexData[i + 1] = position.y;
	m_vertexData[i + 2] = texCoord.x;
	m_vertexData[i + 3] = texCoord.y;
}

void rImmediateBuffer::SetVertex(size_t index, float x, float y){
	size_t i = index * 2;

	m_vertexData[i] = x;
	m_vertexData[i + 1] = y;
}

void rImmediateBuffer::SetVertex(size_t index, float x, float y, float u, float v){
	size_t i = index * 4;

	m_vertexData[i] = x;
	m_vertexData[i + 1] = y;
	m_vertexData[i + 2] = u;
	m_vertexData[i + 3] = v;
}

void rImmediateBuffer::SetVertex(size_t index, const rVector3& position){
	size_t i = index * 3;

	m_vertexData[i] = position.x;
	m_vertexData[i + 1] = position.y;
	m_vertexData[i + 2] = position.z;
}

void rImmediateBuffer::SetVertex(size_t index, const rVector3& position, const rVector2& texCoord){
	size_t i = index * 5;

	m_vertexData[i] = position.x;
	m_vertexData[i + 1] = position.y;
	m_vertexData[i + 2] = position.z;
	m_vertexData[i + 3] = texCoord.x;
	m_vertexData[i + 4] = texCoord.y;
}

void rImmediateBuffer::SetVertex(size_t index, float x, float y, float z){
	size_t i = index * 3;

	m_vertexData[i] = x;
	m_vertexData[i + 1] = y;
	m_vertexData[i + 2] = z;
}

void rImmediateBuffer::SetVertex(size_t index, float x, float y, float z, float u, float v){
	size_t i = index * 5;

	m_vertexData[i] = x;
	m_vertexData[i + 1] = y;
	m_vertexData[i + 2] = z;
	m_vertexData[i + 3] = u;
	m_vertexData[i + 4] = v;
}

void rImmediateBuffer::PushVertex(const rVector2& position){
	m_vertexData.push_back(position.x);
	m_vertexData.push_back(position.y);
}

void rImmediateBuffer::PushVertex(const rVector2& position, const rVector2& texCoord){
	PushVertex(position);
	PushVertex(texCoord);
}

void rImmediateBuffer::PushVertex(float x, float y){
	m_vertexData.push_back(x);
	m_vertexData.push_back(y);
}

void rImmediateBuffer::PushVertex(float x, float y, float u, float v){
	m_vertexData.push_back(x);
	m_vertexData.push_back(y);
	m_vertexData.push_back(u);
	m_vertexData.push_back(v);
}

void rImmediateBuffer::PushVertex(const rVector3& position){
	m_vertexData.push_back(position.x);
	m_vertexData.push_back(position.y);
	m_vertexData.push_back(position.z);
}

void rImmediateBuffer::PushVertex(const rVector3& position, const rVector2& texCoord){
	PushVertex(position);
	PushVertex(texCoord);
}

void rImmediateBuffer::PushVertex(float x, float y, float z){
	m_vertexData.push_back(x);
	m_vertexData.push_back(y);
	m_vertexData.push_back(z);
}

void rImmediateBuffer::PushVertex(float x, float y, float z, float u, float v){
	m_vertexData.push_back(x);
	m_vertexData.push_back(y);
	m_vertexData.push_back(z);
	m_vertexData.push_back(u);
	m_vertexData.push_back(v);
}

void rImmediateBuffer::PushIndex(unsigned short v1){
	m_indexData.push_back(v1);
}

void rImmediateBuffer::PushIndex(unsigned short v1, unsigned int v2){
	m_indexData.push_back(v1);
	m_indexData.push_back(v2);
}

void rImmediateBuffer::PushIndex(unsigned short v1, unsigned int v2, unsigned int v3){
	m_indexData.push_back(v1);
	m_indexData.push_back(v2);
	m_indexData.push_back(v3);
}

void rImmediateBuffer::SetIndexBuffer(const unsigned short* indices, size_t indexCount){
	m_indexData.resize(indexCount);
	memcpy(&m_indexData[0], indices, indexCount * sizeof(unsigned short));
}

void rImmediateBuffer::AppendIndexBuffer(const unsigned short* indices, size_t indexCount) {
	for (size_t i = 0; i < indexCount; i++) {
		m_indexData.push_back(indices[i]);
	}
}

void rImmediateBuffer::TransformVertex(size_t i, const rMatrix4& matrix){
	size_t index = VertexDataArrayIndex(i);

	rVector3 v(m_vertexData[index], m_vertexData[index + 1], m_vertexData[index + 2]);
	matrix.TransformVector3(v);
	SetVertex(i, v);
}

size_t rImmediateBuffer::VertexDataArrayIndex(size_t index) const{
	return ( m_texCoords ? m_vertexSize + 2 : m_vertexSize) * index;
}

char* rImmediateBuffer::IndexData() const{
	if (m_indexData.size() == 0){
		return NULL;
	}
	else{
		return (char*)&m_indexData[0];
	}
}

size_t rImmediateBuffer::IndexDataSize() const{
	return m_indexData.size() * sizeof (rIndexArray::value_type);
}

size_t rImmediateBuffer::IndexCount() const{
	return m_indexData.size();
}

rGeometryType rImmediateBuffer::GeometryType() const{
	return m_geometryType;
}
