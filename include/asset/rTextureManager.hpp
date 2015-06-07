#ifndef R_TEXTUREMANAGER_HPP
#define R_TEXTUREMANAGER_HPP

#include <map>
#include <memory>
#include <functional>

#include "rBuild.hpp"
#include "rGraphicsDevice.hpp"
#include "rFileSystem.hpp"

#include "rAssetManager.hpp"
#include "rTexture.hpp"
#include "rTextureData.hpp"
#include "rTextureFile.hpp"

class rTextureManager : public rAssetManager<rTexture, rTextureData, rTextureFile>{
public:
	rTextureManager(rGraphicsDevice* graphicsDevice, rFileSystem* fileSystem);

protected:
	virtual rTexture* CreateAssetFromData(const rTextureData& textureData, const rString& name) override;
	virtual void DisposeAsset(rTexture* texture) override;

private:
	rGraphicsDevice* m_graphicsDevice;
};

#endif