#ifndef R_MATERIAL_HPP
#define R_MATERIAL_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rAsset.hpp"
#include "rTexture2D.hpp"
#include "rColor.hpp"

class rMaterial : public rAsset{
public:
	rMaterial(const rString& name);
	
	rTexture2D* GetTexture(const rString& name) const;
	void SetTexture(const rString& name, rTexture2D* texture);
	size_t NumTextures() const;
	
	bool GetColor(const rString& name, rColor& color) const;
	void SetColor(const rString& name, const rColor& color);
	size_t NumColors() const;
	
	virtual rAssetType Type() const;
	
private:
	rColorMap m_colors;
	rTextureMap m_textures;
};

#endif