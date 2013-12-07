#ifndef RI_CONTENTMANAGER_HPP
#define RI_CONTENTMANAGER_HPP

#include <map>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rTexture2D.hpp"
#include "rMaterial.hpp"
#include "rShader.hpp"
#include "rGeometry.hpp"
#include "rFont.hpp"
#include "rModel.hpp"

class riContentManager{
public:
	virtual rTexture2D* GetTextureAsset(const rString& name) const = 0;
	virtual rShader* GetShaderAsset(const rString& name) const = 0;
	virtual rMaterial* GetMaterialAsset(const rString& name) const = 0;
	virtual rGeometry* GetGeometryAsset(const rString& name) const = 0;
	virtual rFont* GetFontAsset(const rString& name) const = 0;
	virtual rModel* GetModelAsset(const rString& name) const = 0;
	virtual rSkeleton* GetSkeletonAsset(const rString& name) const = 0;
};

#endif
