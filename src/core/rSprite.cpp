#include "rSprite.hpp"

rSprite::rSprite(const rString& id, rEngine* engine)
	:rActor3(id, engine)
{
	m_sizeSet = false;
}

rSprite::rSprite(const rString& id, rEngine* engine, rTexture* texture)
	:rActor3(id, engine)
{
	m_sizeSet = false;
	m_texture = texture;
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
	m_sizeSet = true;
}

void rSprite::SetSize(float x, float y) {
	m_size.Set(x, y);
	m_sizeSet = true;
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

rTexture* rSprite::GetTexture() const {
	return m_texture;
}

void rSprite::SetTexture(rTexture* texture) {
	m_texture = texture;
}

void rSprite::Draw() {
	rVector2 position(m_position.x, m_position.y);

	if (m_sizeSet) {
		m_engine->renderer->SpriteBatch()->RenderTexture(m_texture, position, m_size);
	}
	else {
		m_engine->renderer->SpriteBatch()->RenderTexture(m_texture, position);
	}
		
}

rString rSprite::ClassName() const {
	return "rSprite";
}