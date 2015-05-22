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

class rMaterialBase{
};

class RECONDITE_API rMaterial : public rMaterialBase, public rAsset{
public:
	rMaterial(int assetid, const rString& name, const rString& path);
	
	virtual rAssetType Type() const;

	void SetDiffuseTexture(rTexture2D* diffuseTexture);
	rTexture2D* DiffuseTexture() const;

	void SetDiffuseColor(const rColor& diffuseColor);
	rColor DiffuseColor() const;

	void SetPointSize(float pointSize);
	float PointSize() const;

	rShader* Shader() const;
	void SetShader(rShader* shader);
private:
	rShader* m_shader;
	rTexture2D* m_diffuseTexture;
	rColor m_diffuseColor;
	float m_pointSize;
};

typedef std::map<rString, rMaterial*> rMaterialMap;
typedef rMaterialMap::iterator rMaterialItr;
typedef rMaterialMap::const_iterator rMaterialConstItr;
typedef std::pair<rString, rMaterial*> rMaterialMapEntry;

#endif
