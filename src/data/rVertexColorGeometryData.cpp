#include "data/rVertexColorGeometryData.hpp"

void rVertexColorGeometryData::TransformVertex(size_t index, const rMatrix4& transform){
	if (index < m_vertices.size()){
		rVertexColorVertex& vertex = m_vertices[index];

		transform.TransformVector3(vertex.position);
		transform.TransformVector3(vertex.normal);
		vertex.normal.Normalize();
	}
}

void rVertexColorGeometryData::PushVertex(const rVector3& position, const rVector3& normal){
	rVector4 white(1.0f, 1.0f, 1.0f, 1.0f);
	rVertexColorVertex vertex(position, normal, white);
	m_vertices.push_back(vertex);
}

void rVertexColorGeometryData::GetVertex(size_t index, rVector3* position, rVector3* normal) const{
	if (index < m_vertices.size()){
		const rVertexColorVertex& vertex = m_vertices[index];

		if (position) *position = vertex.position;
		if (normal) *normal = vertex.normal;
	}
}

size_t rVertexColorGeometryData::VertexCount() const{
	return m_vertices.size();
}

char* rVertexColorGeometryData::VertexData() const{
	return (char*)&m_vertices[0];
}

size_t rVertexColorGeometryData::VertexDataSize() const{
	return m_vertices.size() * sizeof(rVertexColorVertex);
}

void rVertexColorGeometryData::SetColorForVertices(size_t startingIndex, const rColor& color){
	SetColorForVertices(startingIndex, m_vertices.size() - 1, color);
}

void rVertexColorGeometryData::SetColorForVertices(size_t startingIndex, size_t endingIndex, const rColor& color){
	rVector4 c(color.red / 255.0f, color.green / 255.0f, color.blue / 255.0f, color.alpha / 255.0f);

	if (m_vertices.size() > 0){
		size_t end = std::min(endingIndex, m_vertices.size() - 1);
		for (size_t i = startingIndex; i <= end; i++){
			m_vertices[i].color = c;
		}
	}
}

rGeometryProfile rVertexColorGeometryData::GeometryProfile() const{
	return rGeometryProfile::VERTEXCOLOR;
}

void rVertexColorGeometryData::PushVertex(const rVector3& position, const rVector3& normal, const rColor& color){
	rVector4 c(color.red / 255.0f, color.green / 255.0f, color.blue / 255.0f, color.alpha / 255.0f);
	rVertexColorVertex vertex(position, normal, c);
	m_vertices.push_back(vertex);
}

void rVertexColorGeometryData::Clear(){
	m_vertices.clear();
}