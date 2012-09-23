#include "rAsset.hpp"

rAsset::rAsset(int assetId , const rString& name){
	m_name = name;
	m_assetId = assetId;
	m_dependants = 1;
}

void rAsset::SetAssetSourceInfo(rAssetSource source, const wxString& path){
	m_source = source;
	m_path = path;
}

int rAsset::AssetId() const{
	return m_assetId;
}

rString rAsset::Name() const{
	return m_name;
}

rAssetSource rAsset::Source() const{
	return m_source;
}

rString rAsset::Path() const{
	return m_path;
}

int rAsset::Dependants() const{
	return m_dependants;
}

void rAsset::SetDependantCount(int dependants){
	m_dependants = 0;
}