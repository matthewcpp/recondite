#include "data/rAssetManifestData.hpp"

rAssetManifestData::~rAssetManifestData(){
	Clear();
}

void rAssetManifestData::AddManifestEntry(rAssetType type, const rString& name, const rString& path){
	m_assets.push_back(new rAssetManifestEntry(type, name, path));
}

rAssetManifestEntry* rAssetManifestData::GetManifestEntry(size_t index) const{
	if (index < m_assets.size())
		return m_assets[index];
	else
		return NULL;
}

rString rAssetManifestData::GetPath() const{
	return m_path;
}

void rAssetManifestData::SetPath(const rString& path){
	m_path = path;
}

size_t rAssetManifestData::AssetCount() const{
	return m_assets.size();
}

void rAssetManifestData::Clear(){
	for (size_t i =0; i < m_assets.size(); i++)
		delete m_assets[i];

	m_assets.clear();
	m_path.clear();
}
