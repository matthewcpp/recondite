#ifndef R_FONTMANAGER_HPP
#define R_FONTMANAGER_HPP

#include "rBuild.hpp"
#include "rFileSystem.hpp"
#include "rString.hpp"

#include "rTextureManager.hpp"
#include "rFont.hpp"
#include "rFontData.hpp"

class RECONDITE_API rFontManager {
public:
	rFontManager(rFileSystem* fileSystem, rTextureManager* textureManager);
	~rFontManager();

public:
	Font::Family* LoadFromData(recondite::FontData& fontData, const rString& name);
	Font::Family* LoadFromPath(const rString& path, const rString& name);
	Font::Family* Get(const rString& name);

	rTexture* GetFontTexture(Font::Face* face);

	int Delete(const rString& name);

	void Clear();

	Font::Face* SystemDefault();

private:
	struct Impl;
	Impl* _impl;
};

#endif