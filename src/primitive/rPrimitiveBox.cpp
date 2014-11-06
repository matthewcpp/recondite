#include "primitive/rPrimitiveBox.hpp"

rPrimitiveBox::rPrimitiveBox(const rString& id, rEngine* engine)
	:rPrimitive(id, engine)
{
	

	m_width = 1.0f;
	m_height = 1.0f;
	m_depth = 1.0f;
}


void rPrimitiveBox::Draw(){
	rAlignedBox3 box = Box();
	m_engine->renderer->RenderWireBox(box, m_color);
}



rString rPrimitiveBox::ClassName() const{
	return "PrimitiveBox";
}

rAlignedBox3 rPrimitiveBox::Box() const{
	rAlignedBox3 box;

	float halfWidth = m_width / 2.0f;
	float halfDepth = m_depth / 2.0f;

	box.min.Set( m_position.x - halfWidth, m_position.y, m_position.z - halfDepth);
	box.max.Set(m_position.x + halfDepth, m_position.y + m_height, m_position.z + halfDepth);

	return box;
}

float rPrimitiveBox::Width() const{
	return m_width;
}

void rPrimitiveBox::SetWidth(float width){
	m_width = width;
}

float rPrimitiveBox::Height() const{
	return m_height;
}

void rPrimitiveBox::SetHeight(float height){
	m_height = height;
}

float rPrimitiveBox::Depth() const{
	return m_depth;
}

void rPrimitiveBox::SetDepth(float depth){
	m_depth = depth;
}