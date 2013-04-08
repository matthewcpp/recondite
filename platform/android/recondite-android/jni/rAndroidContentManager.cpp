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
	LoadMaterialFromAsset(path, name);
}

rMaterial* rAndroidContentManager::LoadMaterialFromAsset(const rString& path, const rString& name){
	rAndroidAsset asset;
	rMaterial* material;
	m_error = OpenAsset(path, asset);

	if (!m_error){
		rMaterialData materialData(*(asset.assetData));
		material = LoadMaterial(materialData, name);
	}

	return material;
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
    rShaderData data;

    data.SetShaderData(coloredVertexShader, coloredFragmentShader);
    LoadShader(data, "default_colored");

    data.SetShaderData(texturedVertexShader, texturedFragmentShader);
    LoadShader(data, "default_textured");
}
