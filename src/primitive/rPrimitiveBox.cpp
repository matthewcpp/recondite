#include "primitive/rPrimitiveBox.hpp"

rPrimitiveBox::rPrimitiveBox(const rString& id, rEngine* engine)
	:rActor3(id, engine)
{
	m_box = rAlignedBox3::NullBox;
	m_color = rColor::White;
}


void rPrimitiveBox::Draw(rEngine& engine){
	engine.renderer->RenderWireBox(m_box, m_color);
}

void rPrimitiveBox::SetColor(const rColor& color){
	m_color = color;
}

rColor rPrimitiveBox::Color() const{
	return m_color;
}

rString rPrimitiveBox::ClassName() const{
	return "PrimitiveBox";
}

rAlignedBox3 rPrimitiveBox::Box() const{
	return m_box;
}

void rPrimitiveBox::SetBox(const rAlignedBox3& box){
	m_box = box;
}