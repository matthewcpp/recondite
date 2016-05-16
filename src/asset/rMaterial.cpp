#include "asset/rMaterial.hpp"

rMaterial::rMaterial()
{
	m_pointSize = 1.0f;
	m_diffuseColor = rColor::White;
	m_diffuseTexture = nullptr;
}

void rMaterial::SetDiffuseTexture(rTexture* diffuseTexture){
	m_diffuseTexture = diffuseTexture;
}

rTexture* rMaterial::DiffuseTexture() const{
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