#ifndef R_CONTENTMANAGER_HPP
#define R_CONTENTMANAGER_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rGraphicsDevice.hpp"

#include "rTexture2D.hpp"

class rContentManager{
public:
	rContentManager(rGraphicsDevice* graphicsDevice);
	virtual ~rContentManager();
	
	virtual rTexture2D* GetTextureAsset(const rString& name);
	virtual rTexture2D* ImportTextureAssetFromFile(const rString& path , const rString& name);
	virtual bool RemoveTextureAsset(const rString& name);
	
	virtual void UnloadAssets();

	virtual rContentError GetError() const = 0;
	
protected:
	
	rGraphicsDevice* m_graphicsDevice;
};

#endif