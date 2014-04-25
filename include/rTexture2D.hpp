#ifndef R_TEXTURE2D_HPP
#define R_TEXTURE2D_HPP

#include <map>
#include <vector>

#include "rBuild.hpp"
#include "rDefs.hpp"
#include "rString.hpp"

#include "rAsset.hpp"

class RECONDITE_API rTexture2D : public rAsset{
public:
	
	rTexture2D(int width, int height , int bpp, unsigned int graphicsDeviceId, int assetid, const rString& name, const rString& path);
	
	int Width() const;
	int Height() const;
	int GraphicsDeviceID() const;
	int Bpp() const;
	
	virtual rAssetType Type() const;
	
private:
	
	int m_width , m_height;
	int m_bpp;
	unsigned int m_graphicsDeviceId;
};

typedef std::map<rString, rTexture2D*> rTextureMap;
typedef rTextureMap::iterator rTextureItr;
typedef rTextureMap::const_iterator rTextureConstItr;
typedef std::pair<rString, rTexture2D*> rTextureMapEntry;

typedef std::vector<rTexture2D*> rTextureArray;
#endif