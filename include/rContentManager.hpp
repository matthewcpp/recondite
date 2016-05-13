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

#include "asset/rTextureManager.hpp"
#include "asset/rShaderManager.hpp"
#include "asset/rGeometryManager.hpp"
#include "asset/rMaterialManager.hpp"
#include "asset/rFontManager.hpp"
#include "asset/rModelManager.hpp"

class RECONDITE_API rContentManager{
public:
	rContentManager(rGraphicsDevice* graphicsDevice, rFileSystem* fileSystem);
	virtual ~rContentManager();

public:
	rFileSystem* FileSystem();

	rTextureManager* Textures();
	rShaderManager* Shaders();
	rGeometryManager* Geometry();
	rMaterialManager* Materials();
	rFontManager* Fonts();
	rModelManager* Models();
	

public:
	void Clear();
	virtual void InitDefaultAssets(const rString& defaultAssetPath) = 0;

private:

	rGraphicsDevice* m_graphicsDevice;
	rFileSystem* m_fileSystem;

	std::unique_ptr<rTextureManager> m_textures;
	std::unique_ptr<rShaderManager> m_shaders;
	std::unique_ptr<rGeometryManager> m_geometry;
	std::unique_ptr<rMaterialManager> m_materials;
	std::unique_ptr<rFontManager> m_fonts;
	std::unique_ptr<rModelManager> m_models;
};

#endif
