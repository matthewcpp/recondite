#ifndef R_CONTENTMANAGER_HPP
#define R_CONTENTMANAGER_HPP

#include <map>
#include <fstream>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rGraphicsDevice.hpp"

#include "rTexture2D.hpp"
#include "data/rTexture2DData.hpp"

#include "rMaterial.hpp"
#include "data/rMaterialData.hpp"

#include "rShader.hpp"
#include "data/rShaderData.hpp"

class rContentManager{
public:
	rContentManager(rGraphicsDevice* graphicsDevice);
	virtual ~rContentManager();
	
	rTexture2D* GetTextureAsset(const rString& name) const;
	rTexture2D* LoadTexture(const rTexture2DData& textureData, const rString& name);
	virtual rTexture2D* LoadTextureFromPath(const rString& path, const rString& name);
	rTexture2D* GetOrLoadTexture(const rString& textureName, const rString& texturePath);
	rContentError RemoveTextureAsset(const rString& name);
	size_t NumTextures() const;
	
public:
	rShader* GetShaderAsset(const rString& name) const;
	rShader* LoadShader(const rShaderData& shaderData, const rString& name);
	virtual rShader* LoadShaderFromPath(const rString& path, const rString& name);
	rShader* GetOrLoadShader(const rString& shaderName, const rString& shaderPath);
	rContentError RemoveShaderAsset(const rString& name);
	size_t NumShaders() const;
	
public:
	rMaterial* GetMaterialAsset(const rString& name) const;
	rMaterial* LoadMaterial(const rMaterialData& materialData, const rString& name);
	virtual rMaterial* LoadMaterialFromPath(const rString& path, const rString& name);
	rContentError RemoveMaterialAsset(const rString& name);
	size_t NumMaterials() const;
	
public:
	
	void UnloadAssets();
    virtual void InitDefaultAssets();

	rContentError GetLastError() const;
	
protected:
	
	void ReleaseAsset(rAsset* asset);
	
	virtual void Init();
	virtual void Uninit();
	
	rGraphicsDevice* m_graphicsDevice;
	rContentError m_error;
	
	rTextureMap m_textures;
	rShaderMap m_shaders;
	rMaterialMap m_materials;
	
	int GetNextAssetId();
	
private:
	void UnloadTextures();
	void UnloadShaders();
	void UnloadMaterials();
	
	bool LoadTexturesForMaterial(const rMaterialData& materialData, rMaterial* material);
	
	int m_nextAssetId;
};

#endif