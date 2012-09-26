#include "rMaterial.hpp"

rMaterial::rMaterial(const rString& name)
	:rAsset(name)
{
	m_color.Set(255,255,255,255);
	m_diffuse = NULL;
}

rColor rMaterial::Color() const{
	return m_color;
}

void rMaterial::SetColor(const rColor& color){
	m_color = color;
}

rTexture2D* rMaterial::DiffuseTex() const{
	return m_diffuse;
}

void rMaterial::SetDiffuseTex(rTexture2D* diffuse){
	m_diffuse = diffuse;
}

rAssetType rMaterial::Type() const{
	return rASSET_MATERIAL;
}