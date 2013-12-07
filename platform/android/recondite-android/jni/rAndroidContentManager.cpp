#include "rAndroidContentManager.hpp"

rAndroidAsset::rAndroidAsset(){
	rawAssetData = NULL;
	assetDataSize = 0;
	assetData = NULL;
}

rAndroidAsset::~rAndroidAsset(){
	if (rawAssetData)
		delete[] rawAssetData;

	if (assetData)
		delete assetData;
}

rAndroidContentManager::rAndroidContentManager(AAssetManager* androidAssets, rGraphicsDevice* graphicsDevice)
:rContentManager(graphicsDevice)
{
	m_androidAssets = androidAssets;
}

rFont* rAndroidContentManager::LoadFontFromPath(const rString& path, const rString& name){
	return LoadFontFromAsset(path, name);
}

rFont* rAndroidContentManager::LoadFontFromAsset(const rString& path, const rString& name){
	rAndroidAsset asset;
	rFont* font = NULL;
	m_error = OpenAsset(path, asset);

	if (!m_error){
		rFontData fontData;
		fontData.LoadFontDataFromStream(*(asset.assetData));
		font = LoadFont(fontData, name);
	}

	return font;
}

rTexture2D* rAndroidContentManager::LoadTextureFromPath(const rString& path, const rString& name){
	return LoadTextureFromAsset(path, name);
}

rTexture2D* rAndroidContentManager::LoadTextureFromAsset(const rString& path, const rString& name){
	rAndroidAsset asset;
	rTexture2D* texture = NULL;
	m_error = OpenAsset(path, asset);

	if (!m_error){
		rTexture2DData textureData(*(asset.assetData));
		texture = LoadTexture(textureData, name);
	}

	return texture;
}

rMaterial* rAndroidContentManager::LoadMaterialFromPath(const rString& path, const rString& name){
	return LoadMaterialFromAsset(path, name);
}

rMaterial* rAndroidContentManager::LoadMaterialFromAsset(const rString& path, const rString& name){
	rAndroidAsset asset;
	rMaterial* material = NULL;
	m_error = OpenAsset(path, asset);

	if (!m_error){
		rMaterialData materialData(*(asset.assetData));
		material = LoadMaterial(materialData, name);
	}

	return material;
}

rGeometry* rAndroidContentManager::LoadGeometryFromPath(const rString& path, const rString& name){
	return LoadGeometryFromAsset(path, name);
}

rGeometry* rAndroidContentManager::LoadGeometryFromAsset(const rString& path, const rString& name){
	rAndroidAsset asset;
	rGeometry* geometry;
	m_error = OpenAsset(path, asset);

	if (!m_error){
		rGeometryData geometryData(*(asset.assetData));
		geometry = LoadGeometry(geometryData, name);
	}

	return geometry;
}

rModel* rAndroidContentManager::LoadModelFromPath(const rString& path, const rString& name){
	return LoadModelFromAsset(path, name);
}

rModel* rAndroidContentManager::LoadModelFromAsset(const rString& path, const rString& name){
	rAndroidAsset asset;
	rModel* model;
	m_error = OpenAsset(path, asset);

	if (!m_error){
		rModelData modelData;
		modelData.LoadFromStream(*(asset.assetData));
		model = LoadModel(modelData, name);
	}

	return model;
}

rSkeleton* rAndroidContentManager::LoadSkeletonFromPath(const rString& path, const rString& name){
	return LoadSkeletonFromAsset(path, name);
}

rSkeleton* rAndroidContentManager::LoadSkeletonFromAsset(const rString& path, const rString& name){
	rAndroidAsset asset;
	rSkeleton* skeleton = NULL;
	m_error = OpenAsset(path, asset);

	if (!m_error){
		skeleton = new rSkeleton();
		rSkeletonData skeletonData;
		skeletonData.ReadFromStream(*(asset.assetData), *skeleton);
		m_skeletons[name] = skeleton;
	}

	return skeleton;
}

rContentError rAndroidContentManager::OpenAsset(const rString& path, rAndroidAsset& androidAsset){
	AAsset* asset = AAssetManager_open(m_androidAssets, path.c_str(), AASSET_MODE_BUFFER);

	if (asset){
		androidAsset.assetDataSize = AAsset_getLength(asset);
		androidAsset.rawAssetData = new char[androidAsset.assetDataSize];

		int totalRead = 0;

		while (totalRead < androidAsset.assetDataSize){
			int result = AAsset_read(asset, androidAsset.rawAssetData + totalRead, androidAsset.assetDataSize - totalRead);
			totalRead += result;
		}

		androidAsset.assetData = new std::istrstream(androidAsset.rawAssetData, androidAsset.assetDataSize);
		return rCONTENT_ERROR_NONE;
	}
	else
		return rCONTENT_ERROR_FILE_NOT_FOUND;
}

void rAndroidContentManager::InitDefaultAssets(){
	#include "rOpenGLDefaultShaders.inl"

    rShaderData shaderData;

    shaderData.SetShaderData(coloredVertexShader, coloredFragmentShader);
    rShader* result = LoadShader(shaderData, "default_colored");

    shaderData.SetShaderData(pointVertexShader, coloredFragmentShader);
	result = LoadShader(shaderData, "default_points");

    shaderData.SetShaderData(texturedVertexShader, texturedFragmentShader);
    result = LoadShader(shaderData, "default_textured");

    rMaterialData materialData;
    materialData.SetShader("default_colored", "");
    materialData.SetParameter( rMATERIAL_PARAMETER_COLOR , "fragColor", "255 255 255 255");
	LoadMaterial(materialData, "default_colored");

	materialData.SetShader("default_points", "");
	materialData.SetParameter( rMATERIAL_PARAMETER_FLOAT , "recPointSize", "1");
	LoadMaterial(materialData, "default_points");
}
