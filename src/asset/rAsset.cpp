#include "rAsset.hpp"

rAsset::rAsset(int assetid, const rString& name, const rString& path){
	m_name = name;
	m_assetId = assetid;
	m_path = path;
	
	m_retainCount = 0;
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