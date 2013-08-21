#ifndef R_ANDROID_CONTENTMANAGER_HPP
#define R_ANDROID_CONTENTMANAGER_HPP

#include <backward/strstream>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rLog.hpp"

#include "rContentManager.hpp"
#include "rTexture2D.hpp"
#include  "rOpenGLGraphicsDevice.hpp"

#include "android/asset_manager.h"

struct rAndroidAsset{
	rAndroidAsset();
	~rAndroidAsset();

	char* rawAssetData;
	int assetDataSize;
	std::istrstream* assetData;
};

class rAndroidContentManager : public rContentManager{
public:
	rAndroidContentManager(AAssetManager* androidAssets, rGraphicsDevice* graphicsDevice);
	virtual rTexture2D* LoadTextureFromPath(const rString& path, const rString& name);
	rTexture2D* LoadTextureFromAsset(const rString& path, const rString& name);

	virtual rMaterial* LoadMaterialFromPath(const rString& path, const rString& name);
	rMaterial* LoadMaterialFromAsset(const rString& path, const rString& name);

	void InitDefaultAssets();
private:

	rContentError OpenAsset(const rString& path, rAndroidAsset& androidAsset);

private:
	AAssetManager* m_androidAssets;
};

#endif
