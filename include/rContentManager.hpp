#ifndef R_CONTENTMANAGER_HPP
#define R_CONTENTMANAGER_HPP

#include <map>
#include <list>
#include <fstream>
#include <memory>

#include "rBuild.hpp"
#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rGraphicsDevice.hpp"
#include "rFileSystem.hpp"

#include "interface/riResourceManager.hpp"

#include "asset/rTextureManager.hpp"
#include "asset/rShaderManager.hpp"
#include "asset/rFontManager.hpp"
#include "asset/rModelManager.hpp"

#include "asset/rAssetManifest.hpp"

using namespace recondite;

class RECONDITE_API rContentManager{
public:
	rContentManager(rGraphicsDevice* graphicsDevice, rFileSystem* fileSystem, iResourceManager* resourceManager);
	virtual ~rContentManager();

public:
	rFileSystem* FileSystem();

	rTextureManager* Textures();
	rShaderManager* Shaders();
	rFontManager* Fonts();
	rModelManager* Models();

	bool LoadFromManifest(const recondite::AssetManifest& contentData);

public:
	void Clear();
	virtual void InitDefaultAssets(const rString& defaultAssetPath) = 0;

private:

	rGraphicsDevice* m_graphicsDevice;
	rFileSystem* m_fileSystem;
	iResourceManager* m_resourceManager;

	std::unique_ptr<rTextureManager> m_textures;
	std::unique_ptr<rShaderManager> m_shaders;
	std::unique_ptr<rFontManager> m_fonts;
	std::unique_ptr<rModelManager> m_models;
};

#endif
