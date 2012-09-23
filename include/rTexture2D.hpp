#ifndef R_TEXTURE2D_HPP
#define R_TEXTURE2D_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rAsset.hpp"

class rTexture2D : public rAsset{
public:
	
	rTexture2D(int assetId , const rString& name, int width, int height , unsigned int graphicsDeviceId);
	
	int Width() const;
	int Height() const;
	int GraphicsDeviceID() const;
	
	virtual rAssetType Type() const;
	
private:
	
	int m_width , m_height;
	unsigned int m_graphicsDeviceId;
};

#endif