#include "asset/rMaterialData.hpp"

rMaterialData::rMaterialData(){
	m_diffuseColor = rColor::White;
}

rString rMaterialData::Name() const{
	return m_name;
}

void rMaterialData::SetName(const rString& name){
	m_name = name;
}

rString rMaterialData::DiffuseTextureName() const{
	return m_diffuseTetureName;
}

void rMaterialData::SetDiffuseTextureName(const rString& name){
	m_diffuseTetureName = name;
}

rColor rMaterialData::DiffuseColor() const{
	return m_diffuseColor;
}

void rMaterialData::SetDiffuseColor(const rColor& color){
	m_diffuseColor = color;
}