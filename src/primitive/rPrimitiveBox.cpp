#include "primitive/rPrimitiveBox.hpp"

rPrimitiveBox::rPrimitiveBox(const rString& name, const rAlignedBox3& box)
	:rActor3(name, rVector3::ZeroVector)
{
	m_box = box;
	m_color = rColor::White;
}

rPrimitiveBox::rPrimitiveBox(const rString& name, const rAlignedBox3& box, const rColor& color)
	:rActor3(name, rVector3::ZeroVector)
{
	m_box = box;
	m_color = color;
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