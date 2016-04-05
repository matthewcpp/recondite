#include "asset/rTexture.hpp"

rTexture::rTexture(const rString& name, int width, int height, int bpp, unsigned int graphicsDeviceId)
{
	m_size.Set(width, height);
	m_bpp = bpp;
	m_graphicsDeviceId = graphicsDeviceId;
	m_name = name;
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