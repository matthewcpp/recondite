#ifndef R_MATERIAL_HPP
#define R_MATERIAL_HPP

#include <map>

#include "rBuild.hpp"
#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rTexture.hpp"
#include "rColor.hpp"
#include "rMatrix4.hpp"
#include "rShader.hpp"

#include "rPropertyCollection.hpp"

class RECONDITE_API rMaterial {
public:
	rMaterial(const rString& name);

	void SetDiffuseTexture(rTexture* diffuseTexture);
	rTexture* DiffuseTexture() const;

	void SetDiffuseColor(const rColor& diffuseColor);
	rColor DiffuseColor() const;

	void SetPointSize(float pointSize);
	float PointSize() const;

	rShader* Shader() const;
	void SetShader(rShader* shader);

	rString Name() const;

private:
	rShader* m_shader;
	rTexture* m_diffuseTexture;
	rColor m_diffuseColor;
	float m_pointSize;

	rString m_name;
};

#endif
