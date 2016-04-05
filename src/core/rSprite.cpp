#include "rSprite.hpp"

rSprite::rSprite(const rString& id, rEngine* engine)
	:rActor3(id, engine)
{

}

void rSprite::SetPosition2d(const rVector2& position) {
	m_position.x = position.x;
	m_position.y = position.y;
}

rVector2 rSprite::Position2d() const {
	return rVector2(m_position.x, m_position.y);
}

void rSprite::SetSize(const rVector2& size) {
	m_size = size;
}

void rSprite::SetSize(float x, float y) {
	m_size.Set(x, y);
}

rVector2 rSprite::GetSize() const {
	return m_size;
}

void rSprite::SetRenderDepth(float depth) {
	m_position.z = depth;
}

float rSprite::RenderDepth() const {
	return m_position.z;
}