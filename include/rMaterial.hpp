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

#include "rPropertyCollection.hpp"

class RECONDITE_API rMaterial : public rAsset{
public:
	rMaterial(rShader* shader, int assetid, const rString& name, const rString& path);
	
	void SetTexture(const rString& name, rTexture2D* texture);
	void SetColor(const rString& name, const rColor& color);
	void SetFloat(const rString& name, float value);
	
	void GetParameterNames(rArrayString& names) const;
	
	rShader* Shader() const;
	
	virtual rAssetType Type() const;

	const rPropertyCollection& Parameters() const;
	
private:
	rPropertyCollection m_parameters;
	
	rShader* m_shader;
};

typedef std::map<rString, rMaterial*> rMaterialMap;
typedef rMaterialMap::iterator rMaterialItr;
typedef rMaterialMap::const_iterator rMaterialConstItr;
typedef std::pair<rString, rMaterial*> rMaterialMapEntry;

#endif
