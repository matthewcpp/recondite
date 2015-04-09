#include "data/rTexCoordGeometryData.hpp"

void rTexCoordGeometryData::Clear(){
	m_vertexData.clear();
	m_vertexBoneLinks.clear();
}

//vertex operations

void rTexCoordGeometryData::SetVertex(size_t index, const rVector3& v, const rVector3& n, const rVector2& tc){
	if (index < m_vertexData.size()){
		rModelVertex& vertex = m_vertexData[index];

		vertex.position = v;
		vertex.normal = n;
		vertex.texCoord = tc;
	}

}

void rTexCoordGeometryData::PushVertex(const rVector3& position, const rVector3& normal){
	PushVertex(position, normal, rVector2::ZeroVector);
}

void rTexCoordGeometryData::PushVertex(const rVector3& v, const rVector3& n, const rVector2& tc){
	rModelVertex vertex(v, n, tc);
	m_vertexData.push_back(vertex);
}

size_t rTexCoordGeometryData::VertexSizeInBytes() const{
	return sizeof(rModelVertex);
}

void rTexCoordGeometryData::GetVertex(size_t index, rVector3* position, rVector3* normal) const{
	GetVertex(index, position, nullptr, normal);
}

void rTexCoordGeometryData::GetVertex(size_t index, rVector3* position, rVector2* texCoord, rVector3* normal) const {
	if (index >= m_vertexData.size())
		return;

	const rModelVertex& vertex = m_vertexData[index];

	if (position)
		*position = vertex.position;

	if (texCoord)
		*texCoord = vertex.texCoord;

	if (normal)
		*normal = vertex.normal;
}

void rTexCoordGeometryData::TransformVertex(size_t index, const rMatrix4& transform){
	if (index <  m_vertexData.size()){
		rModelVertex& vertex = m_vertexData[index];

		transform.TransformVector3(vertex.position);
		transform.TransformVector3(vertex.normal);
		vertex.normal.Normalize();
	}
}

void rTexCoordGeometryData::Allocate(size_t size){
	m_vertexData.resize(size);
}

char* rTexCoordGeometryData::VertexData() const{
	if (m_vertexData.size())
		return (char*)&m_vertexData[0];
	else
		return NULL;
}

size_t rTexCoordGeometryData::VertexCount() const{
	return m_vertexData.size();
}

size_t rTexCoordGeometryData::VertexDataSize() const{
	return m_vertexData.size() * sizeof(rModelVertexArray::value_type);
}