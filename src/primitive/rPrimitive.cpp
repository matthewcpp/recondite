#include "primitive/rPrimitive.hpp"

rPrimitive::rPrimitive(const rString& id, rEngine* engine)
	:rActor3(id, engine)
{
	m_color = rColor::White;
}

void rPrimitive::SetColor(const rColor& color){
	m_color = color;
}

rColor rPrimitive::Color() const{
	return m_color;
}