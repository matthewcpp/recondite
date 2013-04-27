#include "rAssetManifestData.hpp"

rAssetManifestData::rAssetManifestData(const rString& path){
}

rAssetManifestData::rAssetManifestData(std::istream& stream){
}

rContentError rAssetManifestData::LoadFromFile(const rString& path){
}

rContentError rAssetManifestData::LoadFromStream(std::istream& stream){
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
	
	CreateAssetCategoryXML("texture2d", m_manifestEntries[rASSET_TEXTURE2D], root);
	CreateAssetCategoryXML("shader", m_manifestEntries[rASSET_SHADER], root);
	CreateAssetCategoryXML("material", m_manifestEntries[rASSET_SHADER], root);
	
	xml.WriteToStream(stream);
	
	return m_error;
}

rContentError rAssetManifestData::ReadAssetCategory(rAssetType type, rXMLElement* parent){
	return rCONTENT_ERROR_NONE;
}

void rAssetManifestData::CreateAssetCategoryXML(const rString& name, const rAssetManifestEntryMap& category, rXMLElement* parent){	
	for (rAssetManifestEntryConstItr it = category.begin(); it != category.end(); ++it){
		rAssetManifestEntry& assetEntry = it->second;
		
		rXMLElement* assetNode = parent->CreateChild(name);
		assetNode->CreateChild("name", assetEntry.name);
		assetNode->CreateChild("path", assetEntry.path);
	}
}

rContentError rAssetManifestData::AddManifestEntry(rAssetType type, const rString& name, const rString& path){
	if (type >= rASSET_NUM_TYPES)
		return rCONTENT_ERROR_UNKNOWN_ASSET_TYPE;
	
	if (m_manifestEntries[type].count(name))
		return rCONTENT_ERROR_ASSET_NAME_ALREADY_PRESENT;
	
	rAssetManifestEntry entry(type, name, path);
}

rContentError rAssetManifestData::DeleteManifestEntry(rAssetType type, const rString& name){
	if (type >= rASSET_NUM_TYPES)
		return rCONTENT_ERROR_UNKNOWN_ASSET_TYPE;
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
		m_manifestEntries.clear();
	
	m_error = rCONTENT_ERROR_NONE;
	m_path.clear();
}
