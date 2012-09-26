#include "rAsset.hpp"

rAsset::rAsset(const rString& name){
	m_name = name;
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