#include "rMaterial.hpp"

rMaterial::rMaterial(rShader* shader, int assetid, const rString& name, const rString& path)
	:rAsset(assetid, name, path)
{
	m_shader = shader;
}

rShader* rMaterial::Shader() const{
	return m_shader;
}

void rMaterial::SetDiffuseTexture(rTexture2D* diffuseTexture){
	m_diffuseTexture = diffuseTexture;
}

rTexture2D* rMaterial::DiffuseTexture() const{
	return m_diffuseTexture;
}

void rMaterial::SetDiffuseColor(const rColor& diffuseColor){
	m_diffuseColor = diffuseColor;
}

rColor rMaterial::DiffuseColor() const{
	return m_diffuseColor;
}

rAssetType rMaterial::Type() const{
	return rASSET_MATERIAL;
}