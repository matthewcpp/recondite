#include "rAsset.hpp"

rAsset::rAsset(const rString& name){
	m_name = name;
}

rString rAsset::Name() const{
	return m_name;
}

rString rAsset::Path() const{
	return m_path;
}