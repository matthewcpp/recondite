#include "rMaterial.hpp"

rMaterial::rMaterial(const rString& name)
	:rAsset(name)
{

}

rTexture2D* rMaterial::GetTexture(const rString& name) const{
	rTextureConstItr result = m_textures.find(name);
	
	if (result == m_textures.end())
		return NULL;
	else
		return result->second;
}

void rMaterial::SetTexture(const rString& name, rTexture2D* texture){
	m_textures[name] = texture;
}

size_t rMaterial::NumTextures() const{
	return m_textures.size();
}

bool rMaterial::GetColor(const rString& name, rColor& color) const{
	rColorConstItr result = m_colors.find(name);
	
	if (result == m_colors.end()){
		return false;
	}
	else{
		color = result->second;
		return true;
	}
}

void rMaterial::SetColor(const rString& name, const rColor& color){
	m_colors[name] = color;
}

size_t rMaterial::NumColors() const{
	return m_colors.size();
}

rAssetType rMaterial::Type() const{
	return rASSET_MATERIAL;
}