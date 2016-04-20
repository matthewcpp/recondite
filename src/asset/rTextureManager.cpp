#include "asset/rTextureManager.hpp"

rTextureManager::rTextureManager(rGraphicsDevice* graphicsDevice, rFileSystem* fileSystem)
	:rAssetManager<rTexture, rTextureData, rTextureFile>(fileSystem)
{
	m_graphicsDevice = graphicsDevice;
}

rTexture* rTextureManager::CreateAssetFromData(const rTextureData& textureData, const rString& name){
	unsigned int textureId = m_graphicsDevice->CreateTexture(textureData.Width(), textureData.Height(), textureData.Bpp(), textureData.Data());
	return new rTexture(name, textureData.Width(), textureData.Height(), textureData.Bpp(), textureId);
}

void rTextureManager::DisposeAsset(rTexture* texture){
	m_graphicsDevice->UnregisterTexture(texture->GraphicsDeviceID());
}

#include "xml/rXMLDocument.hpp"
#include "rPath.hpp"

bool rTextureManager::LoadAtlas(const rString& path, const rString& name){
	//first load source texture image
	rString dir, file;
	rPath::Split(path, &dir, &file, nullptr);
	rString texturePath = rPath::Assemble(dir, file, "rtex");

	rTexture* texture = LoadFromPath(texturePath, name);

	if (!texture) return false;

	auto atlasFile = m_fileSystem->GetReadFileRef(path);

	rTextureAtlasData textureAtlasData;
	rContentError error = textureAtlasData.Read(*atlasFile);

	if (error == rContentError::Error) return false;

	for (size_t i = 0; i < textureAtlasData.GetNumEntries(); i++){
		auto entry = textureAtlasData.GetEntry(i);
		rTexture* atlasTexture = new rTexture(entry->name, entry->textureSize, texture->Bpp(), entry->uvOrigin, entry->uvSize, texture->GraphicsDeviceID());
		AddAsset(entry->name, atlasTexture);
	}

	return true;
}