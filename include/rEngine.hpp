#ifndef R_ENGINE_HPP
#define R_ENGINE_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rGraphicsDevice.hpp"
#include "rContentManager.hpp"

#include "rAssetResource.hpp"

class rEngine{
public:
	virtual rGraphicsDevice* GraphicsDevice() = 0;
	virtual rContentManager* ContentManager() = 0;
	
	virtual bool AddAssetResource(rAssetResource* resource) = 0;
	virtual bool RemoveAssetResource(rAssetResource* resource) = 0;
	
	virtual ~rEngine() {}
};

#endif