#ifndef R_FONTMANAGER_HPP
#define R_FONTMANAGER_HPP

#include <map>
#include <memory>
#include <functional>

#include "rBuild.hpp"
#include "rFileSystem.hpp"

#include "rAssetManager.hpp"
#include "rTextureManager.hpp"

#include "rFont.hpp"
#include "rFontData.hpp"
#include "rFontFile.hpp"

class RECONDITE_API rFontManager : public rAssetManager < rFont, rFontData, rFontFile > {
public:
	rFontManager(rFileSystem* fileSystem, rTextureManager* textureManager);

protected:
	virtual rFont* CreateAssetFromData(const rFontData& fontData, const rString& name) override;
	virtual void DisposeAsset(rFont* font) override;

private:
	rTextureManager* m_textureManager;
};

#endif