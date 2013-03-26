#include "rMaterial.hpp"

rMaterial::rMaterial(unsigned int shaderProgramId, int assetid, const rString& name, const rString& path)
	:rAsset(assetid, name, path)
{
	m_shaderProgramId = shaderProgramId;
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

unsigned int rMaterial::ShaderProgramId(){
	return m_shaderProgramId;
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