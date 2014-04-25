#ifndef R_MATERIAL_HPP
#define R_MATERIAL_HPP

#include <map>

#include "rBuild.hpp"
#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rAsset.hpp"
#include "rTexture2D.hpp"
#include "rColor.hpp"
#include "rMatrix4.hpp"
#include "rShader.hpp"

union rMaterialParameterValue{
	rTexture2D* m_texture2d;
	char m_color[4];
	float m_float;
};

struct RECONDITE_API rMaterialParameter{
	rMaterialParameterType m_type;
	rMaterialParameterValue m_value;
	
	bool GetColor(rColor& color);
	rTexture2D* GetTexture();
	float GetFloat();
};

typedef std::map<rString, rMaterialParameter> rMaterialParameterMap;
typedef rMaterialParameterMap::iterator rMaterialParameterItr;
typedef rMaterialParameterMap::const_iterator rMaterialParameterConstItr;
typedef std::pair<rString, rMaterialParameter> rMaterialParameterEntry;

class RECONDITE_API rMaterial : public rAsset{
public:
	rMaterial(rShader* shader, int assetid, const rString& name, const rString& path);
	
	void SetTexture(const rString& name, rTexture2D* texture);
	void SetColor(const rString& name, const rColor& color);
	void SetFloat(const rString& name, float value);
	
	void GetParameterNames(rArrayString& names) const;
	bool GetParameter(const rString& name, rMaterialParameter& param);
	
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
