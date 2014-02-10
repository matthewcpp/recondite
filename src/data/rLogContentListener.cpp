#include "data/rLogContentListener.hpp"

void rLogContentListener::BeginManifestLoad(const rString& path, int total){
	rLog::Info("Begin Loading manifest: %s", path.c_str());
}

void rLogContentListener::ManifestLoadProgress(rAssetType type, const rString& name, const rString& path, int current, int total){
	rString typeStr = rAsset::StringForType(type);
	rLog::Info("Loaded %s %s from %s", typeStr.c_str(), name.c_str(), path.c_str());
}

void rLogContentListener::ManifestLoadError(rAssetType type, const rString& name, const rString& path, rContentError error, int current, int total){
	rString typeStr = rAsset::StringForType(type);
	rLog::Error("Error %d loading %s %s from %s", (int)error, typeStr.c_str(), name.c_str(), path.c_str());
}

void rLogContentListener::EndManifestLoad(const rString& path){
	rLog::Info("Finished Loading manifest: %s", path.c_str());
}
	
void rLogContentListener::AssetLoadComplete(rAssetType type, const rString& name, const rString& path){
	
}

void rLogContentListener::AssetLoadError(rAssetType type, const rString& name, const rString& path, rContentError error){
	
}

void rLogContentListener::AssetUnloaded(rAssetType type, const rString& name){
	
}