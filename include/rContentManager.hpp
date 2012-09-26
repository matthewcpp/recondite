#ifndef R_CONTENTMANAGER_HPP
#define R_CONTENTMANAGER_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rTexture2D.hpp"

class rContentManager{
public:
	virtual ~rContentManager() {}
	
	virtual rTexture2D* GetTextureAsset(const rString& name) = 0;
	virtual rTexture2D* ImportTextureAssetFromFile(const rString& path , const rString& name) = 0;
	virtual bool RemoveTextureAsset(const rString& name) = 0;
	
	virtual void UnloadAssets() = 0;

	virtual rContentError GetError() const = 0;
};

#endif