#include "asset/rTexture.hpp"

rTexture::rTexture(const rString& name, int width, int height, int bpp, unsigned int graphicsDeviceId)
{
	m_width = width;
	m_height = height;
	m_bpp = bpp;
	m_graphicsDeviceId = graphicsDeviceId;
	m_name = name;
}

int rTexture::Width() const{
	return m_width;
}

int rTexture::Height() const{
	return m_height;
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