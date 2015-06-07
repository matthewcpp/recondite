#ifndef R_LOGCONTENTLISTENER_HPP
#define R_LOGCONTENTLISTENER_HPP

#include "rBuild.hpp"

#include "rContentListener.hpp"

#include "rLog.hpp"

class RECONDITE_API rLogContentListener : public rContentListener{
public:
	virtual void BeginManifestLoad(const rString& path, int total);
	virtual void ManifestLoadProgress(rAssetType type, const rString& name, const rString& path, int current, int total);
	virtual void ManifestLoadError(rAssetType type, const rString& name, const rString& path, rContentError error, int current, int total);
	virtual void EndManifestLoad(const rString& path);
	
	virtual void AssetLoadComplete(rAssetType type, const rString& name, const rString& path);
	virtual void AssetLoadError(rAssetType type, const rString& name, const rString& path, rContentError error);
	virtual void AssetUnloaded(rAssetType type, const rString& name);
};

#endif
