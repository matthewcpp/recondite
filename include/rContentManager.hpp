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
	
	virtual rTexture2D* GetTextureAsset(const rString& name) const;
	virtual rTexture2D* LoadTexture(const rTexture2DData& textureData, const rString& name);
	rTexture2D* GetOrLoadTexture(const rString& textureName, const rString& texturePath);
	virtual rContentError RemoveTextureAsset(const rString& name);
	virtual size_t NumTextures() const;
	
public:
	virtual rShader* GetShaderAsset(const rString& name) const;
	virtual rShader* LoadShader(const rShaderData& shaderData, const rString& name);
	rShader* GetOrLoadShader(const rString& shaderName, const rString& shaderPath);
	virtual rContentError RemoveShaderAsset(const rString& name);
	virtual size_t NumShaders() const;
	
public:
	virtual rMaterial* GetMaterialAsset(const rString& name) const;
	virtual rMaterial* LoadMaterial(const rMaterialData& materialData, const rString& name);
	virtual rContentError RemoveMaterialAsset(const rString& name);
	virtual size_t NumMaterials() const;
	
public:
	
	virtual void UnloadAssets();

	virtual rContentError GetLastError() const;
	
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