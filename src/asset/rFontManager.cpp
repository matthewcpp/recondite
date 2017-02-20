#include "asset/rFontManager.hpp"

#include <map>
#include <memory>

#include "rPath.hpp"

struct rFontManager::Impl{
	rTextureManager* textureManager;
	rFileSystem* fileSystem;
	std::map<rString, std::unique_ptr<Font::Family>> fonts;

	Font::Family systemDefault;

	Impl(rFileSystem* _fileSystem, rTextureManager* _textureManager)
	: fileSystem(_fileSystem), textureManager(_textureManager) {}
};

rFontManager::rFontManager(rFileSystem* fileSystem, rTextureManager* textureManager){
	_impl = new Impl(fileSystem, textureManager);
}

rFontManager::~rFontManager(){
	delete _impl;
}

Font::Family* rFontManager::LoadFromData(recondite::FontData& fontData, const rString& name) {
	if (Get(name) == 0) {
		rTexture* texture = _impl->textureManager->Load(*fontData.GetTextureData(), name + "::Texture");

		if (texture) {
			Font::Family* family = fontData.ReleaseFamily();
			family->SetName(name);

			_impl->fonts.emplace(name, family);

			return family;
		}
	}
	
	return nullptr;
}

Font::Family* rFontManager::LoadFromPath(const rString& path, const rString& name){
	if (Get(name)) return nullptr;

	auto fontFile = _impl->fileSystem->OpenReadFileRef(path);
	if (!fontFile) return nullptr;

	recondite::FontData fontData;
	int error = fontData.Read(*fontFile);

	_impl->fileSystem->CloseReadFileRef(fontFile);

	if (!error) {
		return LoadFromData(fontData, name);
	}
	else {
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

Font::Face* rFontManager::SystemDefault(){
	return Get("__default_font__")->GetFace(14, Font::Style::Normal);
}