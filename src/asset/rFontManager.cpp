#include "asset/rFontManager.hpp"

struct rFontManager::Impl{
	rTextureManager* textureManager;
	rFileSystem* fileSystem;

	Impl(rFileSystem* _fileSystem, rTextureManager* _textureManager)
	: fileSystem(_fileSystem), textureManager(_textureManager) {}
};

rFontManager::rFontManager(rFileSystem* fileSystem, rTextureManager* textureManager){
	_impl = new Impl(fileSystem, textureManager);
}

rFontManager::~rFontManager(){
	delete _impl;
}

Font::Family* rFontManager::LoadFromPath(const rString& path, const rString& name){
	return nullptr;
}

Font::Family* rFontManager::Get(const rString& name){
	return nullptr;
}

int rFontManager::Delete(const rString& name){
	return 0;
}

void rFontManager::Clear(){

}