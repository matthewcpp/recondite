#ifndef R_ASSET_RESOURCE_HPP
#define R_ASSET_RESOURCE_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

#include <vector>

struct rAssetInfo{
	int assetId;
	rAssetType type;
	wxString name;
	int filesize;
	rUnsigedByteArray buffer;
	int dependants;
};

class rAssetResource{
public:
	virtual bool GetAsset(int assetId, rAssetInfo& data) = 0;
	virtual bool UpdateAsset(rAssetInfo& info) = 0;
	virtual bool DeleteAsset(int assetId) = 0;
};

#endif