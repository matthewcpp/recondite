#include "rAsset.hpp"

rAsset::rAsset(int assetid, const rString& name, const rString& path){
	m_name = name;
	m_assetId = assetid;
	m_path = path;
	
	m_retainCount = 0;
}

rAssetType rAsset::TypeForString(const rString& str){
	if (str == "texture2d")
		return rASSET_TEXTURE2D;
	else if (str == "shader")
		return rASSET_SHADER;
	else if (str == "material")
		return rASSET_MATERIAL;
	else if (str == "model")
		return rASSET_MODEL;
	else if (str == "font")
		return rASSET_FONT;
	else
		return rASSET_UNKNOWN;
}

rString rAsset::StringForType(rAssetType assetType){
	switch (assetType) {
	case rASSET_TEXTURE2D:
		return "texture2d";
	case rASSET_SHADER:
		return "shader";
	case rASSET_MATERIAL:
		return "material";
	case rASSET_MODEL:
		return "model";
	case rASSET_FONT:
		return "font";
	default:
		return "unknown";
	};
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

int rAsset::Retain(){
	return ++m_retainCount;
}

int rAsset::Release(){
	return --m_retainCount;
}

int rAsset::RetainCount() const{
	return m_retainCount;
}