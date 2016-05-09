#ifndef R_TEXTUREMANAGER_HPP
#define R_TEXTUREMANAGER_HPP

#include "rBuild.hpp"
#include "rGraphicsDevice.hpp"
#include "rFileSystem.hpp"

#include "rAssetManager.hpp"
#include "rTexture.hpp"
#include "rTextureData.hpp"

#include "rTextureAtlasData.hpp"

class RECONDITE_API rTextureManager {
public:
	rTextureManager(rGraphicsDevice* graphicsDevice, rFileSystem* fileSystem);
	~rTextureManager();

public:
	rTexture* LoadFromPath(const rString& path, const rString& name);
	rTexture* Load(const rTextureData& textureData, const rString& name);
	rTexture* Get(const rString& name);

	int Delete(const rString& name);

	int LoadAtlasFromPath(const rString& path, const rString& name);

	void Clear();

private:
	struct Impl;
	Impl* _impl;
};

#endif