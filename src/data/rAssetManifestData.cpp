#include "data/rAssetManifestData.hpp"

rAssetManifestData::rAssetManifestData(const rString& path){
	LoadFromFile(path);
}

rAssetManifestData::rAssetManifestData(std::istream& stream){
	LoadFromStream(stream);
}

rContentError rAssetManifestData::LoadFromFile(const rString& path){
	std::ifstream file(path.c_str());
	
	if (file){
		LoadFromStream(file);
	}
	else{
		Clear();
		m_error = rCONTENT_ERROR_FILE_NOT_FOUND;
	}
	
	m_path = path;
	
	return m_error;
}

rContentError rAssetManifestData::LoadFromStream(std::istream& stream){
	Clear();
	
	rXMLDocument xml;
	xml.LoadFromStream(stream);
	
	rXMLElement* root = xml.GetRoot();
	
	for (size_t i = 0; i < root->NumChildren(); i++){
		ReadAsset(root->GetChild(i));
	}
	
	return rCONTENT_ERROR_NONE;
}

rContentError rAssetManifestData::ReadAsset(rXMLElement* asset){
	rString assetTypeName;
	asset->GetAttribute<rString>("type", assetTypeName);
	rAssetType assetType = rAsset::TypeForString(assetTypeName);
	
	if (assetType == rASSET_UNKNOWN)
		return rCONTENT_ERROR_UNKNOWN_ASSET_TYPE;
	
	rXMLElement* assetNameNode = asset->GetFirstChildNamed("name");
	rXMLElement* assetPathNode = asset->GetFirstChildNamed("path");
	
	if (assetNameNode && assetPathNode){
		AddManifestEntry(assetType, assetNameNode->Text(), assetPathNode->Text());
	}
	else{                                                            
		return rCONTENT_ERROR_PARSE_ERROR;
	}
	
	return rCONTENT_ERROR_NONE;
}

rContentError rAssetManifestData::WriteToFile(const rString& path){
	std::ofstream stream(path.c_str());
	
	if (!stream)
		m_error = rCONTENT_ERROR_FILE_NOT_WRITABLE;
	else
		WriteToStream(stream);
	
	stream.close();
	return m_error;
}

rContentError rAssetManifestData::WriteToStream(std::ostream& stream){
	
	if (!stream)
		m_error = rCONTENT_ERROR_STREAM_ERROR;
	
	rXMLDocument xml;
	rXMLElement* root = xml.CreateRoot("manifest");
	root->AddAttribute("version", 1);
	
	CreateAssetCategoryXML(m_manifestEntries[rASSET_TEXTURE2D], root);
	CreateAssetCategoryXML(m_manifestEntries[rASSET_SHADER], root);
	CreateAssetCategoryXML(m_manifestEntries[rASSET_SHADER], root);
	
	xml.WriteToStream(stream);
	
	return m_error;
}

void rAssetManifestData::CreateAssetCategoryXML(const rAssetManifestEntryMap& category, rXMLElement* parent){	
	for (rAssetManifestEntryConstItr it = category.begin(); it != category.end(); ++it){
		const rAssetManifestEntry& assetEntry = it->second;
		
		rXMLElement* assetNode = parent->CreateChild("asset");
		assetNode->AddAttribute<rString>("type",rAsset::StringForType(assetEntry.type));
		assetNode->CreateChild("name", assetEntry.name);
		assetNode->CreateChild("path", assetEntry.path);
	}
}

rContentError rAssetManifestData::AddManifestEntry(rAssetType type, const rString& name, const rString& path){
	if (type < 0 || type >= rASSET_NUM_TYPES)
		return rCONTENT_ERROR_UNKNOWN_ASSET_TYPE;
	
	if (m_manifestEntries[type].count(name))
		return rCONTENT_ERROR_ASSET_NAME_ALREADY_PRESENT;
	
	rAssetManifestEntry entry(type, name, path);
	rAssetManifestMapItem item(name, entry);
	
	m_manifestEntries[type].insert(item);
	
	return rCONTENT_ERROR_NONE;
}

rContentError rAssetManifestData::DeleteManifestEntry(rAssetType type, const rString& name){
	if (type < 0 || type >= rASSET_NUM_TYPES)
		return rCONTENT_ERROR_UNKNOWN_ASSET_TYPE;
	
	if (m_manifestEntries[type].count(name)){
		m_manifestEntries[type].erase(name);
		return rCONTENT_ERROR_NONE;
	}
	else
		return rCONTENT_ERROR_ASSET_NOT_PRESENT;
}

rContentError rAssetManifestData::GetError() const{
	return m_error;
}

rString rAssetManifestData::GetPath() const{
	return m_path;
}

size_t rAssetManifestData::AssetCount(rAssetType type){
	if (type >= rASSET_NUM_TYPES)
		return 0;
	
	return m_manifestEntries[type].size();
}

void rAssetManifestData::Clear(){
	for (size_t i = 0; i < rASSET_NUM_TYPES; i++)
		m_manifestEntries[i].clear();
	
	m_error = rCONTENT_ERROR_NONE;
	m_path.clear();
}
