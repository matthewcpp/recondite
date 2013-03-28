#ifndef RWX_CONTENT_MANAGER_HPP
#define RWX_CONTENT_MANAGER_HPP

#include <string.h>
#include <map>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rContentManager.hpp"
#include "rOpenGLGraphicsDevice.hpp"

#include <wx/wx.h>
#include <wx/filefn.h>

#include "rwxUtils.hpp"
#include "data/rTexture2DData.hpp"


class rwxContentManager : public rContentManager{
public:
	rwxContentManager(rOpenGLGraphicsDevice* graphicsDevice);
        rTexture2D* ImportTextureAssetFromFile(const wxString& path , const wxString& name);
	
private:
	
	rTexture2D* LoadWxImageToGraphicsDevice(wxImage& texture, const wxString& name);
};

#endif