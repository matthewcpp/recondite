#ifndef RWX_CONTENT_MANAGER_HPP
#define RWX_CONTENT_MANAGER_HPP

#include <string.h>
#include <map>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rContentManager.hpp"
#include "rgl/rOpenGLGraphicsDevice.hpp"

#include "wx/wx.h"
#include "wx/filefn.h"
#include "wx/mstream.h"

#include "rwxUtils.hpp"

typedef std::map<rString, rTexture2D*> rTextureMap;
typedef rTextureMap::iterator rTextureItr;
typedef std::pair<rString, rTexture2D*> rTextureMapEntry;;


class rwxContentManager : public rContentManager{
public:
	rwxContentManager(rOpenGLGraphicsDevice* graphicsDevice);
	~rwxContentManager();
	
	virtual rTexture2D* GetTextureAsset(const rString& name);
	virtual rTexture2D* ImportTextureAssetFromFile(const rString& path , const rString& name);
	virtual bool RemoveTextureAsset(const rString& name);
	
	virtual void UnloadAssets();
	
	virtual rContentError GetError() const;
	
private:
	void UnloadTextures();
	bool DeleteTexture(rTexture2D* texture);
	
	rTexture2D* LoadWxImageToGraphicsDevice(wxImage& texture, const wxString& name);
	
	int GetNextAssetId();
	
private:
	rContentError m_error;
	
	rOpenGLGraphicsDevice* m_graphicsDevice;
	
	rTextureMap m_textures;
};

#endif