#include "rAsset.hpp"

rAsset::rAsset(int assetid, const rString& name, const rString& path){
	m_name = name;
	m_assetId = assetid;
	m_path = path;
}

rString rAsset::Name() const{
	return m_name;
}

rString rAsset::Path() const{
	return m_path;
}

int rAsset::AssetId() const{
	return m_assetId;
}