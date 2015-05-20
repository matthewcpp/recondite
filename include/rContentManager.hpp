#ifndef R_CONTENTMANAGER_HPP
#define R_CONTENTMANAGER_HPP

#include <map>
#include <list>
#include <fstream>
#include <memory>

#include "rBuild.hpp"
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
#include "data/rGeometryDataFile.hpp"

#include "rFont.hpp"
#include "data/rFontData.hpp"

#include "rModel.hpp"
#include "data/rModelData.hpp"
#include "data/rModelDataFile.hpp"

#include "rSkeleton.hpp"
#include "data/rSkeletonData.hpp"

#include "data/rAssetManifestData.hpp"
#include "data/rAssetManifestDataFile.hpp"

#include "rContentListener.hpp"

#include "interface/riContentManager.hpp"


#include "stream/rIFileStream.hpp"
#include "stream/rOFileStream.hpp"

typedef std::unique_ptr<rIStream> rIAssetStream;
typedef std::unique_ptr<rOStream> rOAssetStream;

class RECONDITE_API rContentManager : public riContentManager{
public:
	rContentManager(rGraphicsDevice* graphicsDevice);
	virtual ~rContentManager();
	
//Textures
public:
	virtual rTexture2D* GetTextureAsset(const rString& name) const;
	rTexture2D* LoadTexture(const rTexture2DData& textureData, const rString& name);
	virtual rTexture2D* LoadTextureFromPath(const rString& path, const rString& name);
	rTexture2D* GetOrLoadTexture(const rString& textureName, const rString& texturePath);
	rContentError RemoveTextureAsset(const rString& name);
	size_t NumTextures() const;

//Shaders
public:
	virtual rShader* GetShaderAsset(const rString& name) const;
	rShader* LoadShader(const rShaderData& shaderData, const rString& name);
	virtual rShader* LoadShaderFromPath(const rString& path, const rString& name);
	rShader* GetOrLoadShader(const rString& name, const rString& path);
	rContentError RemoveShaderAsset(const rString& name);
	size_t NumShaders() const;

	rShader* DefaultModelShader();
	rShader* DefaultLineShader();
	rShader* DefaultPrimitiveShader();

//Materials
public:
	virtual rMaterial* GetMaterialAsset(const rString& name) const;
	rMaterial* LoadMaterial(const rMaterialData& materialData, const rString& name);
	rMaterial* GetOrLoadMaterial(const rString& name, const rString& path);
	virtual rMaterial* LoadMaterialFromPath(const rString& path, const rString& name);
	rContentError RemoveMaterialAsset(const rString& name);
	size_t NumMaterials() const;
	rMaterial* CreateMaterial(const rString& name);
	
//Geometry
public:
	virtual rGeometry* GetGeometryAsset(const rString& name) const;
	rGeometry* LoadGeometry(const rGeometryData& geometryData, const rString& name);
	rGeometry* GetOrLoadGeometry(const rString& name, const rString& path);
	virtual rGeometry* LoadGeometryFromPath(const rString& path, const rString& name);
	rContentError RemoveGeometryAsset(const rString& name);
	size_t NumGeometry() const;

//Fonts
public:
	virtual rFont* GetFontAsset(const rString& name) const;
	rFont* LoadFont(const rFontData& fontData, const rString& name);
	virtual rFont* LoadFontFromPath(const rString& path, const rString& name);
	rContentError RemoveFontAsset(const rString& name);
	size_t NumFonts();

//Models
public:
	virtual rModel* GetModelAsset(const rString& name) const;
	rModel* LoadModel(rModelData& modelData, const rString& name);
	rContentError RemoveModelAsset(const rString& name);
	virtual rModel* LoadModelFromPath(const rString& path, const rString& name);
	rModel* GetOrLoadModel(const rString& name, const rString& path);
	size_t NumModels() const;
	void GetModelNames(rArrayString& names) const;

//Skeletons
public:
	virtual rSkeleton* GetSkeletonAsset(const rString& name) const;
	virtual rSkeleton* LoadSkeletonFromPath(const rString& path, const rString& name);
	rSkeleton* GetOrLoadSkeleton(const rString& name, const rString& path);
	rContentError RemoveSkeletonAsset(const rString& name);
	size_t NumSkeletons();

//Text
public:
	virtual rIAssetStream LoadTextFromPath(const rString& path);
	virtual rOAssetStream GetWritableFileStream(const rString& path);

//Asset Manifest
public:
	virtual void LoadAssetManifest(const rAssetManifestData& assetManifest);
	virtual void LoadAssetManifestFromPath(const rString& path);

public:
	void UnloadAssets();
	virtual void InitDefaultAssets();

	rContentError GetLastError() const;
	bool ProcessingBatchFile() const;
	
public:
	void AddListener(rContentListener* listener);
	void RemoveListener(rContentListener* listener);
	
private:
	void NotifyManifestBegin(const rString& path, int total);
	void NotifyManifestProgress(rAssetType type, const rString& name, const rString& path, int current, int total);
	void NotifyManifestLoadError(rAssetType type, const rString& name, const rString& path, rContentError error, int current, int total);
	void NotifyManifestEnd(const rString& path);
	
	void NotifyAssetLoadComplete(rAssetType type, const rString& name, const rString& pat);
	void NotifyAssetLoadError(rAssetType type, const rString& name, const rString& path, rContentError error);
	void NotifyAssetUnloaded(rAssetType type, const rString& name);
	
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
	rModelMap m_models;
	rSkeletonMap m_skeletons;
	
	int GetNextAssetId();

private:
		typedef std::list<rContentListener*> rContentListenerList;
	
private:
	void UnloadTextures();
	void UnloadShaders();
	void UnloadMaterials();
	void UnloadGeometry();
	
	bool LoadMaterialDependencies(const rMaterialData& materialData, rMaterial* material);
	void DeleteGeometryBuffers(rGeometry* geometry);
	
	int m_nextAssetId;
	
	rContentListenerList m_listeners;
	bool m_processingBatchFile;
};

#endif
