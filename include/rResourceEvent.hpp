#pragma once

#include "rBuild.hpp"

#include "asset/rModelData.hpp"

enum rResourceEventId {
	rEVT_MODEL_RESOURCE_LOADED
};

class RECONDITE_API rResourceLoadedEvent : public rEvent {
private:
	union DataPtr {
		ModelData* modelData;
	};

	rAssetType assetType;
	DataPtr data;

public:
	inline rAssetType GetAssetType() const;
	inline ModelData* GetModelData() const;

public:
	rResourceLoadedEvent(ModelData* modelData) {
		assetType = rAssetType::Model;
		data.modelData = modelData;
	}
};

inline rAssetType rResourceLoadedEvent::GetAssetType() const {
	return assetType;
}

inline ModelData* rResourceLoadedEvent::GetModelData() const {
	if (assetType == rAssetType::Model)
		return data.modelData;
	else
		return nullptr;
}