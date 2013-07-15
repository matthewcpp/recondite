#include "rMaterial.hpp"

rMaterial::rMaterial(rShader* shader, int assetid, const rString& name, const rString& path)
	:rAsset(assetid, name, path)
{
	m_shader = shader;
}

rTexture2D* rMaterial::GetTexture(const rString& name) const{
	rTexture2D* texture = NULL;
	rMaterialParameterConstItr result = m_parameters.find(name);
	
	if (result != m_parameters.end() && result->second.m_type == rMATERIAL_PARAMETER_TEXTURE2D){
			texture = result->second.m_value.m_texture2d;
	}
	
	return texture;
}

void rMaterial::SetTexture(const rString& name, rTexture2D* texture){
	rMaterialParameter parameter;
	parameter.m_type = rMATERIAL_PARAMETER_TEXTURE2D;
	parameter.m_value.m_texture2d = texture;
	
	m_parameters[name] = parameter;
}

void rMaterial::SetColor(const rString& name, rColor& color){
	rMaterialParameter parameter;
	parameter.m_type = rMATERIAL_PARAMETER_COLOR;
	
	parameter.m_value.m_color[0] = color.red;
	parameter.m_value.m_color[1] = color.green;
	parameter.m_value.m_color[2] = color.blue;
	parameter.m_value.m_color[3] = color.alpha;
	
	m_parameters[name] = parameter;
}

bool rMaterial::GetColor(const rString& name, rColor& color){
	rMaterialParameterConstItr result = m_parameters.find(name);
	
	if (result != m_parameters.end() && result->second.m_type == rMATERIAL_PARAMETER_COLOR){
		
		color.red = result->second.m_value.m_color[0];
		color.green = result->second.m_value.m_color[1];
		color.blue = result->second.m_value.m_color[2];
		color.alpha = result->second.m_value.m_color[3];
		return true;
	}
	else{
		return false;
	}
}

rShader* rMaterial::Shader() const{
	return m_shader;
}

rAssetType rMaterial::Type() const{
	return rASSET_MATERIAL;
}

rMaterialParameterType rMaterial::GetParameterType(const rString& name) const{
	rMaterialParameterType materialType = rMATERIAL_PARAMETER_UNKNOWN;
	rMaterialParameterConstItr result = m_parameters.find(name);
	
	if (result != m_parameters.end())
		materialType = result->second.m_type;
	
	return materialType;
}

void rMaterial::GetParameterNames(rArrayString& names) const{
	names.clear();
	
	for (rMaterialParameterConstItr it = m_parameters.begin(); it != m_parameters.end(); ++it)
		names.push_back(it->first);
}

void rMaterial::GetParameterNamesForType(rArrayString& names, rMaterialParameterType type){
	names.clear();
	
	for (rMaterialParameterConstItr it = m_parameters.begin(); it != m_parameters.end(); ++it){
		if (it->second.m_type == type)
			names.push_back(it->first);
	}
}