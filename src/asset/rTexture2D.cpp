#include "rTexture2D.hpp"

rTexture2D::rTexture2D(int assetId , const rString& name , int width, int height , unsigned int graphicsDeviceId)
:rAsset(assetId , name)
{
	m_width = width;
	m_height = height;
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

rAssetType rTexture2D::Type() const{
	return rASSET_TEXTURE2D;
}