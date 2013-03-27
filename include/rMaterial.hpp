#ifndef R_MATERIAL_HPP
#define R_MATERIAL_HPP

#include <map>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rAsset.hpp"
#include "rTexture2D.hpp"
#include "rColor.hpp"
#include "rMatrix4.hpp"
#include "rShader.hpp"

union rMaterialParameterValue{
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
	rMaterial(rShader* shader, int assetid, const rString& name, const rString& path);
	
	rTexture2D* GetTexture(const rString& name) const;
	void SetTexture(const rString& name, rTexture2D* texture);
	
	rMaterialParameterType GetParameterType(const rString& name) const;
	void GetParameterNames(rArrayString& names) const;
	void GetParameterNamesForType(rArrayString& names, rMaterialParameterType type); 
	
	rShader* Shader() const;
	
	virtual rAssetType Type() const;
	
private:
	rMaterialParameterMap m_parameters;
	
	rShader* m_shader;
};

typedef std::map<rString, rMaterial*> rMaterialMap;
typedef rMaterialMap::iterator rMaterialItr;
typedef rMaterialMap::const_iterator rMaterialConstItr;
typedef std::pair<rString, rMaterial*> rMaterialMapEntry;

#endif