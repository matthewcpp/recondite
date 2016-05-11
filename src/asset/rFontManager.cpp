#include "asset/rFontManager.hpp"

#include <map>
#include <memory>

#include "rPath.hpp"

struct rFontManager::Impl{
	rTextureManager* textureManager;
	rFileSystem* fileSystem;
	std::map<rString, std::unique_ptr<Font::Family>> fonts;

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
	if (Get(name)) return nullptr;

	rString outDir, outName;
	rPath::Split(path, &outDir, &outName, nullptr);

	rString textureFilePath = rPath::Assemble(outDir, name, "rtex");
	if (_impl->textureManager->LoadFromPath(textureFilePath, name + "::Texture") == nullptr)
		return nullptr;

	auto fontFile = _impl->fileSystem->GetReadFileRef(path);
	if (!fontFile) return nullptr;

	std::unique_ptr<Font::Family> fontRef(new Font::Family());
	int error = fontRef->Read(*fontFile);
	if (!error){
		fontRef->SetName(name);
		_impl->fonts.insert(std::make_pair(name, std::move(fontRef)));

		return _impl->fonts[name].get();
	}
	else
	{
		return nullptr;
	}
}

Font::Family* rFontManager::Get(const rString& name){
	auto result = _impl->fonts.find(name);

	if (result == _impl->fonts.end())
		return nullptr;
	else
		return result->second.get();
}

int rFontManager::Delete(const rString& name){
	return 0;
}

void rFontManager::Clear(){

}

rTexture* rFontManager::GetFontTexture(Font::Face* face){
	return _impl->textureManager->Get(face->GetFamily()->GetName() + "::Texture");
}