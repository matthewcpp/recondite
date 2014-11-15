#include "primitive/rPrimitiveCylinder.hpp"

rPrimitiveCylinder::rPrimitiveCylinder(const rString& id, rEngine* engine)
	:rPrimitive(id, engine)
{
	m_radius = 1.0f;
	m_height = 1.0f;
	m_segmentCount = 20;
}

float rPrimitiveCylinder::Radius() const{
	return m_radius;
}

void rPrimitiveCylinder::SetRadius(float radius){
	m_radius = radius;
	InvalidateGeometry();
}

float rPrimitiveCylinder::Height() const{
	return m_height;
}

void rPrimitiveCylinder::SetHeight(float height){
	m_height = height;
	InvalidateGeometry();
}

rString rPrimitiveCylinder::ClassName() const{
	return "PrimitiveCylinder";
}

int rPrimitiveCylinder::SegmentCount() const{
	return m_segmentCount;
}

void rPrimitiveCylinder::SetSegmentCount(int segmentCount){
	m_segmentCount = segmentCount;
	InvalidateGeometry();
}

void rPrimitiveCylinder::CreateGeometry(rGeometryData& geometry){
	rElementBufferData* wireframe = geometry.CreateElementBuffer("wire", rGEOMETRY_LINES);
	rElementBufferData* shaded = geometry.CreateElementBuffer("shaded", rGEOMETRY_TRIANGLES);

	rVector3 position;
	rVector3 normal = rVector3::ZeroVector;
	rVector2 texCoord = rVector2::ZeroVector;

	float step = 360.0f / (float)m_segmentCount;

	for (float angle = 0.0f; angle <= 360.0f; angle += step){
		float radians = rMath::DegreeToRad(angle);
		
		position.Set(std::cos(radians), 0.0f, std::sin(radians));
		position *= m_radius;
		
		geometry.PushVertex(position, normal, texCoord);
	}

	for (float angle = 0.0f; angle <= 360.0f; angle += step){
		float radians = rMath::DegreeToRad(angle);
		
		position.Set(std::cos(radians), m_height, std::sin(radians));
		position *= m_radius;
		
		geometry.PushVertex(position, normal, texCoord);
	}

	//build wireframe indicies
	size_t count =  geometry.VertexCount() / 2;
	for (size_t i = 0; i < count; i++){
		wireframe->Push(i, i + count);

		
		if (i > 0){
			wireframe->Push(i, i - 1);
			wireframe->Push(i + count, i + count - 1);
		}
		
	}

	wireframe->Push(0, count -1);
	wireframe->Push(count, count + count - 1);
}