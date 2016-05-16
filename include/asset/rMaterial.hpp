#ifndef R_MATERIAL_HPP
#define R_MATERIAL_HPP

#include <map>

#include "rBuild.hpp"
#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rTexture.hpp"
#include "rColor.hpp"
#include "rShader.hpp"

#include "rPropertyCollection.hpp"

class RECONDITE_API rMaterial {
public:
	rMaterial();

	void SetDiffuseTexture(rTexture* diffuseTexture);
	rTexture* DiffuseTexture() const;

	void SetDiffuseColor(const rColor& diffuseColor);
	rColor DiffuseColor() const;

	void SetPointSize(float pointSize);
	float PointSize() const;

private:
	rTexture* m_diffuseTexture;
	rColor m_diffuseColor;
	float m_pointSize;
};

#endif
