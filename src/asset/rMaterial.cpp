#include "rMaterial.hpp"

rMaterial::rMaterial(int assetid, const rString& name, const rString& path)
	:rAsset(assetid, name, path)
{
	m_pointSize = 1.0f;
	m_diffuseColor = rColor::White;
	m_diffuseTexture = nullptr;
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

void rMaterial::SetPointSize(float pointSize){
	m_pointSize = pointSize;
}

float rMaterial::PointSize() const{
	return m_pointSize;
}

rAssetType rMaterial::Type() const{
	return rASSET_MATERIAL;
}
