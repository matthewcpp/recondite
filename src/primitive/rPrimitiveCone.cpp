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

void rPrimitiveCone::CreateGeometry(rGeometryData& geometry){
	rElementBufferData* wireframe = geometry.CreateElementBuffer("wire", rGEOMETRY_LINES);
	rElementBufferData* shaded = geometry.CreateElementBuffer("shaded", rGEOMETRY_TRIANGLES);

	rVector3 position(0, m_height, 0);
	rVector3 normal = rVector3::ZeroVector;
	rVector2 texCoord = rVector2::ZeroVector;

	geometry.PushVertex(position, normal, texCoord);

	float step = 360.0f / (float)m_segmentCount;

	for (float angle = 0.0f; angle <= 360.0f; angle += step){
		float radians = rMath::DegreeToRad(angle);
		
		position.Set(std::cos(radians), 0.0f, std::sin(radians));
		position *= m_radius;
		
		geometry.PushVertex(position, normal, texCoord);
	}

	//generate wireframe indicies
	size_t count = geometry.VertexCount();
	for (size_t i = 1; i < count; i++){
		if (i > 0)
			wireframe->Push(0, i);
		if (i > 1)
			wireframe->Push(i, i - 1);
	}
}

int rPrimitiveCone::SegmentCount() const{
	return m_segmentCount;
}

void rPrimitiveCone::SetSegmentCount(int segmentCount){
	m_segmentCount = segmentCount;
	InvalidateGeometry();
}