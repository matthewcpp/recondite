#ifndef R_ASSET_HPP
#define R_ASSET_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

class rAsset{
public:
	rAsset(int assetid, const rString& name, const rString& path);
	virtual ~rAsset() {}
	
	int AssetId() const;
	rString Name() const;
	rString Path() const;
	
	virtual rAssetType Type() const = 0;
	
protected:
	rString m_name;
	rString m_path;
	
	int m_assetId;
};



#endif