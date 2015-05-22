#include "data/rPrimitiveGeometryData.hpp"

void rPrimitiveGeometryData::TransformVertex(size_t index, const rMatrix4& transform){
	if (index < m_vertices.size()){
		rPrimitiveVertex& vertex = m_vertices[index];

		transform.TransformVector3(vertex.position);
		transform.TransformVector3(vertex.normal);

		vertex.normal.Normalize();
	}
}

void rPrimitiveGeometryData::PushVertex(const rVector3& position, const rVector3& normal){
	rPrimitiveVertex vertex(position, normal);
	m_vertices.push_back(vertex);
}

void rPrimitiveGeometryData::GetVertex(size_t index, rVector3* position, rVector3* normal) const{
	if (index < m_vertices.size()){
		const rPrimitiveVertex& vertex = m_vertices[index];

		if (position) *position = vertex.position;
		if (normal) *normal = vertex.normal;
	}
}

size_t rPrimitiveGeometryData::VertexCount() const{
	return m_vertices.size();
}

char* rPrimitiveGeometryData::VertexData() const{
	if (m_vertices.size())
		return (char*)&m_vertices[0];
	else
		return nullptr;
}

size_t rPrimitiveGeometryData::VertexDataSize() const{
	return m_vertices.size() * sizeof(rPrimitiveVertexArray::value_type);
}

rGeometryProfile rPrimitiveGeometryData::GeometryProfile() const{
	return rGeometryProfile::PRIMITIVE;
}