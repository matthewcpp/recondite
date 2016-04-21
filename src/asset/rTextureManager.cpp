#include "asset/rTextureManager.hpp"

#include <map>

#include "rPath.hpp"

struct rTextureManager::Impl{
	rGraphicsDevice* graphicsDevice;
	rFileSystem* fileSystem;
	std::map<rString, std::unique_ptr<rTexture>> textures;

	rTexture* Create(const rTextureData& textureData, const rString& name);
};

rTextureManager::rTextureManager(rGraphicsDevice* graphicsDevice, rFileSystem* fileSystem)
{
	_impl.reset(new Impl());
	_impl->graphicsDevice = graphicsDevice;
	_impl->fileSystem = fileSystem;
}

rTextureManager::~rTextureManager(){}

rTexture* rTextureManager::LoadFromPath(const rString& path, const rString& name){
	if (Get(name)) return nullptr;

	auto textureFile = _impl->fileSystem->GetReadFileRef(path);
	if (!textureFile) return nullptr;

	rTextureData textureData;
	int error = textureData.Read(*textureFile);

	if (error) 
		return nullptr;
	else
		return _impl->Create(textureData, name);
}

rTexture* rTextureManager::Load(const rTextureData& textureData, const rString& name){
	if (Get(name))
		return nullptr;
	else
		return _impl->Create(textureData, name);
}


rTexture* rTextureManager::Impl::Create(const rTextureData& textureData, const rString& name){
	unsigned int textureId = graphicsDevice->CreateTexture(textureData.Width(), textureData.Height(), textureData.Bpp(), textureData.Data());
	rTexture* texture = new rTexture(name, textureData.Width(), textureData.Height(), textureData.Bpp(), textureId);
	std::unique_ptr<rTexture> textureRef(texture);

	textures.insert(std::make_pair(name, std::move(textureRef)));

	return texture;
}

//TODO: make sure dont delete atlas image from a sub texture
int rTextureManager::Delete(const rString& name){
	rTexture* texture = Get(name);

	if (texture){
		_impl->graphicsDevice->UnregisterTexture(texture->GraphicsDeviceID());
		_impl->textures.erase(name);
		return 0;
	}
	else{
		return 1;
	}
}

void rTextureManager::Clear(){
	for (auto& texture : _impl->textures){
		_impl->graphicsDevice->UnregisterTexture(texture.second->GraphicsDeviceID());
	}

	_impl->textures.clear();
}


int rTextureManager::LoadAtlasFromPath(const rString& path, const rString& name){
	//first load source texture image
	rString dir, file;
	rPath::Split(path, &dir, &file, nullptr);
	rString texturePath = rPath::Assemble(dir, file, "rtex");

	rTexture* texture = LoadFromPath(texturePath, name);

	if (!texture) return 1;

	auto atlasFile = _impl->fileSystem->GetReadFileRef(path);

	rTextureAtlasData textureAtlasData;
	int error = textureAtlasData.Read(*atlasFile);

	if (error) return 1;

	//create a texture for each sub item and add it to the map
	for (size_t i = 0; i < textureAtlasData.GetNumEntries(); i++){
		auto entry = textureAtlasData.GetEntry(i);
		if (_impl->textures.count(entry->name)) continue;

		rTexture* atlasTexture = new rTexture(entry->name, entry->textureSize, texture->Bpp(), entry->uvOrigin, entry->uvSize, texture->GraphicsDeviceID());
		std::unique_ptr<rTexture> textureRef(atlasTexture);
		_impl->textures.insert(std::make_pair(entry->name, std::move(textureRef)));
	}

	return 0;
}

rTexture* rTextureManager::Get(const rString& name){
	auto result = _impl->textures.find(name);

	if (result == _impl->textures.end())
		return nullptr;
	else
		return result->second.get();
}