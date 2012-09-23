#ifndef R_CONTENTMANAGER_HPP
#define R_CONTENTMANAGER_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rTexture2D.hpp"
#include "rModel.hpp"
#include "rAssetResource.hpp"

class rContentManager{
public:
	virtual ~rContentManager() {}
	
	virtual bool AddAssetResource(rAssetResource* resource) = 0;
	virtual bool RemoveAssetResource(rAssetResource* resource) = 0;
	
	virtual rTexture2D* GetTextureAsset(int assetId) = 0;
	virtual rTexture2D* ImportTextureAssetFromFile(const rString& path , const rString& name) = 0;
	virtual rTexture2D* ImportTextureAssetFromInfo(rAssetInfo& info) = 0;
	
	virtual rModel* ImportModelAssetFromFile(const rString& path, const rString& name) = 0;
	
	virtual void ReleaseAsset(rAsset* asset) = 0;
	virtual void RetainAsset(rAsset* asset) = 0;
	
	virtual void UnloadAssets() = 0;
	
	virtual void SetBaseAssetId(int assetId) = 0;
	virtual int GetLastAssetId() const = 0;
	virtual rContentError GetError() const = 0;
};

#endif