#include "asset/rTexture.hpp"

rTexture::rTexture(const rString& name, int width, int height, int bpp, unsigned int graphicsDeviceId)
{
	m_size.Set(width, height);
	m_bpp = bpp;
	m_graphicsDeviceId = graphicsDeviceId;
	m_name = name;

	m_uvOrigin.Set(0.0f, 0.0f);
	m_uvSize.Set(1.0f, 1.0f);
}

rTexture::rTexture(const rString& name, const rSize& size, int bpp, const rVector2& uvOrigin, const rVector2 uvSize, unsigned int graphicsDeviceId){
	m_name = name;
	m_size = size;
	m_bpp = bpp;
	m_graphicsDeviceId = graphicsDeviceId;

	m_uvOrigin = uvOrigin;
	m_uvSize = uvSize;
}

int rTexture::Width() const{
	return m_size.x;
}

int rTexture::Height() const{
	return m_size.y;
}

rSize rTexture::Size() const {
	return m_size;
}

int rTexture::GraphicsDeviceID() const{
	return m_graphicsDeviceId;
}

int rTexture::Bpp() const{
	return m_bpp;
}

rString rTexture::Name() const{
	return m_name;
}

const rVector2& rTexture::UVOrigin() const{
	return m_uvOrigin;
}

const rVector2& rTexture::UVSize() const{
	return m_uvSize;
}