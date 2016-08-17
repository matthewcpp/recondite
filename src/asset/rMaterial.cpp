#include "asset/rMaterial.hpp"

rMaterial::rMaterial()
{
	m_diffuseColor = rColor::White;
	m_diffuseTexture = nullptr;
}

void rMaterial::Copy(const rMaterial& material) {
	m_diffuseColor = material.m_diffuseColor;
	m_diffuseTexture = material.m_diffuseTexture;
	m_name = material.m_name;
}