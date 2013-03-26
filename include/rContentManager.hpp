#ifndef R_CONTENTMANAGER_HPP
#define R_CONTENTMANAGER_HPP

#include <map>
#include <fstream>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rGraphicsDevice.hpp"

#include "rTexture2D.hpp"
#include "data/rTexture2DData.hpp"

#include "rMaterial.hpp"

class rContentManager{
public:
	rContentManager(rGraphicsDevice* graphicsDevice);
	virtual ~rContentManager();
	
	virtual rTexture2D* GetTextureAsset(const rString& name) const;
	virtual rTexture2D* LoadTexture(const rTexture2DData& textureData, const rString& name);
	virtual rContentError RemoveTextureAsset(const rString& name);
	virtual size_t NumTextures() const;
	
public:
	rMaterial* CreateMaterialInstance(const rString& name);
	
public:
	
	virtual void UnloadAssets();

	virtual rContentError GetLastError() const;
	
protected:
	
	virtual void Init();
	virtual void Uninit();
	
	rGraphicsDevice* m_graphicsDevice;
	rContentError m_error;
	
	rTextureMap m_textures;
	
	int GetNextAssetId();
	
private:
	void UnloadTextures();
	
	int m_nextAssetId;
};

#endif