#ifndef R_MATERIALMANAGER_HPP
#define R_MATERIALMANAGER_HPP

#include "rBuild.hpp"
#include "rFileSystem.hpp"

#include "rAssetManager.hpp"
#include "rTextureManager.hpp"
#include "rShaderManager.hpp"

#include "rMaterial.hpp"
#include "rMaterialData.hpp"
#include "rMaterialFile.hpp"

class RECONDITE_API rMaterialManager : public rAssetManager < rMaterial, rMaterialData, rMaterialFile > {
public:
	rMaterialManager(rFileSystem* fileSystem, rTextureManager* textureManager, rShaderManager* shaderManager);

public:
	rMaterial* CreateMaterial(const rString& name);

protected:
	virtual rMaterial* CreateAssetFromData(const rMaterialData& materialData, const rString& name) override;
	virtual void DisposeAsset(rMaterial* material) override;

private:
	rShaderManager* m_shaderManager;
	rTextureManager* m_textureManager;

};

#endif