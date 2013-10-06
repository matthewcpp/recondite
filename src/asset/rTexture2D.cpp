#include "rTexture2D.hpp"

rTexture2D::rTexture2D(int width, int height , int bpp, unsigned int graphicsDeviceId, int assetid, const rString& name, const rString& path)
	:rAsset(assetid, name, path)
{
	m_width = width;
	m_height = height;
	m_bpp = bpp;
	m_graphicsDeviceId = graphicsDeviceId;
}

int rTexture2D::Width() const{
	return m_width;
}

int rTexture2D::Height() const{
	return m_height;
}

int rTexture2D::GraphicsDeviceID() const{
	return m_graphicsDeviceId;
}

int rTexture2D::Bpp() const{
	return m_bpp;
}

rAssetType rTexture2D::Type() const{
	return rASSET_TEXTURE2D;
}