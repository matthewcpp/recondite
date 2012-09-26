#ifndef R_ASSET_HPP
#define R_ASSET_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

class rAsset{
public:
	rAsset(const rString& name);
	virtual ~rAsset() {}
	
	int AssetId() const;
	rString Name() const;
	
	rAssetSource Source() const;
	rString Path() const;
	
	virtual rAssetType Type() const = 0;
	
protected:
	rString m_name;
	
	rAssetSource m_source;
	rString m_path;
};



#endif