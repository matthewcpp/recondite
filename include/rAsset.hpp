#ifndef R_ASSET_HPP
#define R_ASSET_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

class rAsset{
public:
	rAsset(int assetId , const rString& name);
	virtual ~rAsset() {}
	
	int AssetId() const;
	rString Name() const;
	
	rAssetSource Source() const;
	rString Path() const;
	
	virtual rAssetType Type() const = 0;
	
	void SetAssetSourceInfo(rAssetSource source, const wxString& path);
	
	int Dependants() const;
	void SetDependantCount(int dependants);
	
protected:
	int m_assetId;
	rString m_name;
	
	rAssetSource m_source;
	rString m_path;
	
	int m_dependants;
};



#endif