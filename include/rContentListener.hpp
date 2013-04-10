#ifndef R_CONTENT_LISTENER_HPP
#define R_CONTENT_LISTENER_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

class rContentListener {
public:

	virtual void BeginBatchLoad(int total) {}
	virtual void BatchLoadProgress(const rString& assetName, rAssetType type, int current, int total) {}
	virtual void BatchLoadError(const rString& assetName, rAssetType type, rContentError error, int current, int total) {}
	virtual void EndBatchLoad() {}
	
	virtual void AssetLoadComplete(const rString& assetName, rAssetType type) {}
	virtual void AssetLoadError(const rString& assetName, rAssetType type, rContentError error) {}
	virtual void AssetUnloaded(const rString& assetName, rAssetType type) {}
};

#endif
