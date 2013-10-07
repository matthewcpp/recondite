#ifndef R_CONTENTMANAGER_HPP
#define R_CONTENTMANAGER_HPP

#include <map>
#include <list>
#include <fstream>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rLog.hpp"

#include "rGraphicsDevice.hpp"
#include "xml/rXMLDocument.hpp"

#include "rTexture2D.hpp"
#include "data/rTexture2DData.hpp"

#include "rMaterial.hpp"
#include "data/rMaterialData.hpp"

#include "rShader.hpp"
#include "data/rShaderData.hpp"

#include "rGeometry.hpp"
#include "data/rGeometryData.hpp"

#include "rFont.hpp"
#include "data/rFontData.hpp"

#include "rContentListener.hpp"

typedef std::list<rContentListener*> rContentListenerList;
typedef rContentListenerList::iterator rContentListenerItr;
typedef rContentListenerList::const_iterator rContentListenerConstItr;

class rContentManager{
public:
	rContentManager(rGraphicsDevice* graphicsDevice);
	virtual ~rContentManager();
	
public:
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
	rGeometry* GetGeometryAsset(const rString& name) const;
	rGeometry* LoadGeometry(const rGeometryData& geometryData, const rString& name);
	rContentError RemoveGeometryAsset(const rString& name);
	size_t NumGeometry() const;
	
public:
	rFont* GetFontAsset(const rString& name) const;
	rFont* LoadFont(const rFontData& fontData, const rString& name);
	rContentError RemoveFontAsset(const rString& name);
	size_t NumFonts();

public:
	virtual rContentError LoadAssetManifestFromPath(const rString& path);
	rContentError LoadAssetManifestFromStream(std::istream& stream);
	void UnloadAssets();
	virtual void InitDefaultAssets();

	rContentError GetLastError() const;
	bool ProcessingBatchFile() const;
	
public:
	void AddListener(rContentListener* listener);
	void RemoveListener(rContentListener* listener);
	
private:
	void NotifyBatchBegin(int total);
	void NotifyBatchProgress(const rString& assetName, rAssetType type, int current, int total);
	void NotifyBatchLoadError(const rString& assetName, rAssetType type, rContentError error, int current, int total);
	void NotifyBatchEnd();
	
	void NotifyAssetLoadComplete(const rString& assetName, rAssetType type);
	void NotifyAssetLoadError(const rString& assetName, rAssetType type, rContentError error);
	void NotifyAssetUnloaded(const rString& assetName, rAssetType type);
	
protected:
	
	void ReleaseAsset(rAsset* asset);
	
	virtual void Init();
	virtual void Uninit();
	
	rGraphicsDevice* m_graphicsDevice;
	rContentError m_error;
	
	rTextureMap m_textures;
	rShaderMap m_shaders;
	rMaterialMap m_materials;
	rGeometryMap m_geometry;
	rFontMap m_fonts;
	
	int GetNextAssetId();
	
private:
	void UnloadTextures();
	void UnloadShaders();
	void UnloadMaterials();
	void UnloadGeometry();
	
	void LoadManifestAssets(rXMLElementArray& assets);
	
	bool LoadMaterialDependencies(const rMaterialData& materialData, rMaterial* material);
	void DeleteGeometryBuffers(rGeometry* geometry);
	
	int m_nextAssetId;
	
	rContentListenerList m_listeners;
	bool m_processingBatchFile;
};

#endif
