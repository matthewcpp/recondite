#ifndef R_MATERIAL_HPP
#define R_MATERIAL_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rAsset.hpp"
#include "rTexture2D.hpp"

class rMaterial : public rAsset{
public:
	rMaterial(int assetId , const rString& name);
	
	rColor Color() const;
	void SetColor(const rColor& color);
	
	rTexture2D* DiffuseTex() const;
	void SetDiffuseTex(rTexture2D* diffuse);
	
	virtual rAssetType Type() const;
	
private:
	rColor m_color;
	rTexture2D* m_diffuse;
};

#endif