#include "primitive/rPrimitiveCone.hpp"

rPrimitiveCone::rPrimitiveCone(const rString& id, rEngine* engine)
	:rPrimitive(id, engine)
{
	m_height = 1.0f;
	m_radius = 1.0f;
	
	m_segmentCount = 20;
}

float rPrimitiveCone::Radius() const{
	return m_radius;
}

void rPrimitiveCone::SetRadius(float radius){
	m_radius = radius;
	InvalidateGeometry();
}

float rPrimitiveCone::Height() const{
	return m_height;
}

void rPrimitiveCone::SetHeight(float height){
	m_height = height;
	InvalidateGeometry();
}

rString rPrimitiveCone::ClassName() const{
	return "PrimitiveCone";
}

void rPrimitiveCone::CreateGeometry(rModelGeometryData& geometry){
	rElementBufferData* wireframe = geometry.CreateElementBuffer("wire", rGEOMETRY_LINES);
	rElementBufferData* shaded = geometry.CreateElementBuffer("shaded", rGEOMETRY_TRIANGLES);

	CreateCircle3d(geometry, rVector3::ZeroVector, m_radius, rVector3::DownVector, m_segmentCount);
	

	for (int i = 0; i < m_segmentCount; i++){
		CreateConeFace(geometry, i + 1, i + 2);
	}

	CreateConeFace(geometry, m_segmentCount, 1);

	
}

void rPrimitiveCone::CreateConeFace(rModelGeometryData& geometry, size_t v1, size_t v2){
	rElementBufferData* wireframe = geometry.GetElementBuffer("wire");
	rElementBufferData* shaded = geometry.GetElementBuffer("shaded");

	float coneAngle = std::atan(m_radius / m_height);

	rVector3 tip = rVector3::UpVector * m_height;
	rVector3 p1, p2, n1, n2;

	geometry.GetVertex(v1, &p1, NULL, NULL);
	n1 = p1.GetNormalized();
	n1 *= std::cos(coneAngle);
	n1.y = std::sin(coneAngle);

	geometry.GetVertex(v2, &p2, NULL, NULL);
	n2 = p1.GetNormalized();
	n2 *= std::cos(coneAngle);
	n2.y = std::sin(coneAngle);

	size_t baseIndex = geometry.VertexCount();
	geometry.PushVertex(tip, n1, rVector2::ZeroVector);
	geometry.PushVertex(p1, n1, rVector2::ZeroVector);
	geometry.PushVertex(p2, n2, rVector2::ZeroVector);
	shaded->Push(baseIndex, baseIndex + 1, baseIndex + 2);

	wireframe->Push(baseIndex, baseIndex + 1);
	wireframe->Push(baseIndex, baseIndex + 2);
}

int rPrimitiveCone::SegmentCount() const{
	return m_segmentCount;
}

void rPrimitiveCone::SetSegmentCount(int segmentCount){
	m_segmentCount = segmentCount;
	InvalidateGeometry();
}