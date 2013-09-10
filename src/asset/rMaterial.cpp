#include "rMaterial.hpp"

bool rMaterialParameter::GetColor(rColor& color){
	if (m_type == rMATERIAL_PARAMETER_COLOR){
		color.red = m_value.m_color[0];
		color.green = m_value.m_color[1];
		color.blue = m_value.m_color[2];
		color.alpha = m_value.m_color[3];
		return true;
	}
	else{
		return false;
	}
}

rTexture2D* rMaterialParameter::GetTexture(){
	if (m_type == rMATERIAL_PARAMETER_TEXTURE2D){
		return m_value.m_texture2d;
	}
	else{
		return NULL;
	}
}

rMaterial::rMaterial(rShader* shader, int assetid, const rString& name, const rString& path)
	:rAsset(assetid, name, path)
{
	m_shader = shader;
}

void rMaterial::SetTexture(const rString& name, rTexture2D* texture){
	rMaterialParameter parameter;
	parameter.m_type = rMATERIAL_PARAMETER_TEXTURE2D;
	parameter.m_value.m_texture2d = texture;
	
	m_parameters[name] = parameter;
}

void rMaterial::SetColor(const rString& name, const rColor& color){
	rMaterialParameter parameter;
	parameter.m_type = rMATERIAL_PARAMETER_COLOR;
	
	parameter.m_value.m_color[0] = color.red;
	parameter.m_value.m_color[1] = color.green;
	parameter.m_value.m_color[2] = color.blue;
	parameter.m_value.m_color[3] = color.alpha;
	
	m_parameters[name] = parameter;
}

rShader* rMaterial::Shader() const{
	return m_shader;
}

rAssetType rMaterial::Type() const{
	return rASSET_MATERIAL;
}


bool rMaterial::GetParameter(const rString& name, rMaterialParameter& param){
	rMaterialParameterConstItr result = m_parameters.find(name);
	
	if (result != m_parameters.end()){
		param = result->second;
		return true;
	}
	else{
		return false;
	}
}

void rMaterial::GetParameterNames(rArrayString& names) const{
	names.clear();
	
	for (rMaterialParameterConstItr it = m_parameters.begin(); it != m_parameters.end(); ++it)
		names.push_back(it->first);
}