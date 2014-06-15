#include "primitive/rPrimitiveBox.hpp"

rPrimitiveBox::rPrimitiveBox(const rString& name, const rAlignedBox3& box)
	:rActor3(name, rVector3::ZeroVector)
{
	m_box = box;
}

void rPrimitiveBox::Draw(rEngine& engine){
	engine.renderer->RenderWireBox(m_box, rColor::Red);
}