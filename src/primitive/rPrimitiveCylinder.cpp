#include "primitive/rPrimitiveCylinder.hpp"

rPrimitiveCylinder::rPrimitiveCylinder(const rString& id, rEngine* engine)
	:rPrimitive(id, engine)
{
	m_radius = 1.0f;
	m_height = 1.0f;
}

float rPrimitiveCylinder::Radius() const{
	return m_radius;
}

void rPrimitiveCylinder::SetRadius(float radius){
	m_radius = radius;
}

float rPrimitiveCylinder::Height() const{
	return m_height;
}

void rPrimitiveCylinder::SetHeight(float height){
	m_height = height;
}

rString rPrimitiveCylinder::ClassName() const{
	return "PrimitiveCylinder";
}

void rPrimitiveCylinder::Draw(){
	rImmediateBuffer geometry(rGEOMETRY_LINES, 3, false);

	float segments = 20.0f;

	float step = 360.0f / segments;

	rVector3 vertex;
	for (float angle = 0.0f; angle <= 360.0f; angle += step){
		float radians = rMath::DegreeToRad(angle);
		
		vertex.Set(std::cos(radians), 0.0f, std::sin(radians));
		vertex *= m_radius;
		
		geometry.PushVertex(vertex);
	}

	for (float angle = 0.0f; angle <= 360.0f; angle += step){
		float radians = rMath::DegreeToRad(angle);
		
		vertex.Set(std::cos(radians), m_height, std::sin(radians));
		vertex *= m_radius;
		
		geometry.PushVertex(vertex);
	}

	//build wireframe indicies
	size_t count =  geometry.VertexCount() / 2;
	for (size_t i = 0; i < count; i++){
		geometry.PushIndex(i, i + count);

		
		if (i > 0){
			geometry.PushIndex(i, i - 1);
			geometry.PushIndex(i + count, i + count - 1);
		}
		
	}

	rMatrix4 transform = TransformMatrix();
	m_engine->renderer->Render3dBuffer(geometry, transform, m_color);
}