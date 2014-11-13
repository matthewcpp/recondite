#include "rMaterial.hpp"

rMaterial::rMaterial(rShader* shader, int assetid, const rString& name, const rString& path)
	:rAsset(assetid, name, path)
{
	m_shader = shader;
}

const rPropertyCollection& rMaterial::Parameters() const{
	return m_parameters;
}

void rMaterial::SetTexture(const rString& name, rTexture2D* texture){
	m_parameters.SetTexture(name, texture);
}

void rMaterial::SetColor(const rString& name, const rColor& color){
	m_parameters.SetColor(name, color);
}

void rMaterial::SetFloat(const rString& name, float value){
	m_parameters.SetFloat(name, value);
}

rShader* rMaterial::Shader() const{
	return m_shader;
}

rAssetType rMaterial::Type() const{
	return rASSET_MATERIAL;
}

void rMaterial::GetParameterNames(rArrayString& names) const{
	m_parameters.GetKeys(names);
}
