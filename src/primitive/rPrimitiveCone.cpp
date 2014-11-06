#include "primitive/rPrimitiveCone.hpp"

rPrimitiveCone::rPrimitiveCone(const rString& id, rEngine* engine)
	:rPrimitive(id, engine)
{
	m_height = 1.0f;
	m_radius = 1.0f;
}

float rPrimitiveCone::Radius() const{
	return m_radius;
}

void rPrimitiveCone::SetRadius(float radius){
	m_radius = radius;
}

float rPrimitiveCone::Height() const{
	return m_height;
}

void rPrimitiveCone::SetHeight(float height){
	m_height = height;
}

rString rPrimitiveCone::ClassName() const{
	return "PrimitiveCone";
}

void rPrimitiveCone::Draw(){
	rImmediateBuffer geometry(rGEOMETRY_LINES, 3, false);

	geometry.PushVertex(0, m_height, 0);

	float segments = 20.0f;

	float step = 360.0f / segments;
	unsigned short index = 1;

	rVector3 vertex;
	for (float angle = 0.0f; angle <= 360.0f; angle += step){
		float radians = rMath::DegreeToRad(angle);
		
		vertex.Set(std::cos(radians), 0.0f, std::sin(radians));
		vertex *= m_radius;
		
		geometry.PushVertex(vertex);
		geometry.PushIndex(index, 0);
		
		if (index > 1){
			geometry.PushIndex(index, index - 1);
		}
		
		index++;
	}

	m_engine->renderer->Render3dBuffer(geometry, m_color);
}