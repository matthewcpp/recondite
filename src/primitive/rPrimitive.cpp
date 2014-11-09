#include "primitive/rPrimitive.hpp"

rPrimitive::rPrimitive(const rString& id, rEngine* engine)
	:rActor3(id, engine)
{
	m_color = rColor::White;

	m_geometryInvalid = true;
}

void rPrimitive::SetColor(const rColor& color){
	m_color = color;
}

rColor rPrimitive::Color() const{
	return m_color;
}

void rPrimitive::InvalidateGeometry(){
	m_geometryInvalid = true;
}

void rPrimitive::Draw(){
	if (m_geometryInvalid){
		CreateGeometry();
		m_geometryInvalid = false;
	}

	rMatrix4 transform = TransformMatrix();
	m_engine->renderer->Render3dBuffer(geometry, transform, m_color);
}