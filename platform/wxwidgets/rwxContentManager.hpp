#ifndef RWX_CONTENT_MANAGER_HPP
#define RWX_CONTENT_MANAGER_HPP

#include <string.h>
#include <map>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rContentManager.hpp"
#include "rAssetResource.hpp"
#include "rOpenGLGraphicsDevice.hpp"

#include "wx/wx.h"
#include "wx/filefn.h"
#include "wx/mstream.h"

#include "rwxUtils.hpp"

#include "rwxAssimpModelImporter.hpp"

typedef std::map<int, rTexture2D*> rTextureMap;
typedef rTextureMap::iterator rTextureItr;
typedef std::pair<int, rTexture2D*> rTextureMapEntry;;


class rwxContentManager : public rContentManager{
public:
	rwxContentManager(rOpenGLGraphicsDevice* graphicsDevice);
	~rwxContentManager();
	
	virtual bool AddAssetResource(rAssetResource* resource);
	virtual bool RemoveAssetResource(rAssetResource* resource);
	
	virtual rTexture2D* GetTextureAsset(int assetId);
	
	virtual rTexture2D* ImportTextureAssetFromFile(const rString& path , const rString& name);
	virtual rTexture2D* ImportTextureAssetFromInfo(rAssetInfo& info);
	
	virtual rModel* ImportModelAssetFromFile(const rString& path, const rString& name);
	
	virtual void ReleaseAsset(rAsset* asset);
	virtual void RetainAsset(rAsset* asset);
	
	virtual void UnloadAssets();
	
	virtual void SetBaseAssetId(int assetId);
	virtual int GetLastAssetId() const;
	virtual rContentError GetError() const;
	
	virtual rModel* ImportModelData(rModelData& modelData);
	
private:
	
	rAsset* GetAsset(int assetId);
	bool RemoveTextureAsset(rTexture2D* texture);
	
	rTexture2D* LoadWxImageToGraphicsDevice(wxImage& texture, const wxString& name, int assetId);
	
	int GetNextAssetId();
	
private:
	rContentError m_error;
	
	rAssetResource* m_resource;
	rOpenGLGraphicsDevice* m_graphicsDevice;
	
	
	rTextureMap m_textures;
	int m_baseAssetId;
};

#endif