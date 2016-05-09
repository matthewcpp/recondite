#ifndef R_FONTMANAGER_HPP
#define R_FONTMANAGER_HPP

#include "rBuild.hpp"
#include "rFileSystem.hpp"
#include "rString.hpp"

#include "rTextureManager.hpp"
#include "rFont.hpp"

class RECONDITE_API rFontManager {
public:
	rFontManager(rFileSystem* fileSystem, rTextureManager* textureManager);
	~rFontManager();

public:
	Font::Family* LoadFromPath(const rString& path, const rString& name);
	Font::Family* Get(const rString& name);

	int Delete(const rString& name);

	void Clear();

private:
	struct Impl;
	Impl* _impl;
};

#endif