#ifndef R_MATERIAL_HPP
#define R_MATERIAL_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rAsset.hpp"
#include "rTexture2D.hpp"
#include "rColor.hpp"
#include "rMatrix4.hpp"

union rMaterialParameterValue{
	int m_int;
	float m_float;
	float m_vec3[3];
	float m_matrix4[16];
	rTexture2D* m_texture2d;
};

struct rMaterialParameter{
	rMaterialParameterType m_type;
	rMaterialParameterValue m_value;
};

typedef std::map<rString, rMaterialParameter> rMaterialParameterMap;
typedef rMaterialParameterMap::iterator rMaterialParameterItr;
typedef rMaterialParameterMap::const_iterator rMaterialParameterConstItr;
typedef std::pair<rString, rMaterialParameter> rMaterialParameterEntry;

class rMaterial : public rAsset{
public:
	rMaterial(unsigned int materialId, int assetid, const rString& name, const rString& path);
	
	rTexture2D* GetTexture(const rString& name) const;
	void SetTexture(const rString& name, rTexture2D* texture);
	
	rMaterialParameterType GetParameterType(const rString& name) const;
	void GetParameterNames(rArrayString& names) const;
	
	unsigned int ShaderProgramId();
	
	virtual rAssetType Type() const;
	
private:
	rMaterialParameterMap m_parameters;
	
	unsigned int m_shaderProgramId;
};

#endif