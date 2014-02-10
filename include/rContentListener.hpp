#ifndef R_CONTENT_LISTENER_HPP
#define R_CONTENT_LISTENER_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

class rContentListener {
public:

	virtual void BeginManifestLoad(const rString& path, int total) {}
	virtual void ManifestLoadProgress(rAssetType type, const rString& name, const rString& path, int current, int total) {}
	virtual void ManifestLoadError(rAssetType type, const rString& name, const rString& path, rContentError error, int current, int total) {}
	virtual void EndManifestLoad(const rString& path) {}
	
	virtual void AssetLoadComplete(rAssetType type, const rString& name, const rString& path){}
	virtual void AssetLoadError(rAssetType type, const rString& name, const rString& path, rContentError error){}
	virtual void AssetUnloaded(rAssetType type, const rString& name){}
};

#endif
