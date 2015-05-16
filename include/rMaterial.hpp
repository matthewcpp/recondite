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
	
	rShader* Shader() const;
	
	virtual rAssetType Type() const;

	void SetDiffuseTexture(rTexture2D* diffuseTexture);
	rTexture2D* DiffuseTexture() const;

	void SetDiffuseColor(const rColor& diffuseColor);
	rColor DiffuseColor() const;
	
private:

	rTexture2D* m_diffuseTexture;
	rColor m_diffuseColor;
	
	rShader* m_shader;
};

typedef std::map<rString, rMaterial*> rMaterialMap;
typedef rMaterialMap::iterator rMaterialItr;
typedef rMaterialMap::const_iterator rMaterialConstItr;
typedef std::pair<rString, rMaterial*> rMaterialMapEntry;

#endif
