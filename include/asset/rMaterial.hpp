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

	inline void SetDiffuseTexture(rTexture* diffuseTexture);
	inline rTexture* DiffuseTexture() const;

	inline void SetDiffuseColor(const rColor& diffuseColor);
	inline rColor DiffuseColor() const;

	inline rString GetName() const;
	inline void SetName(const rString& name);

	void Copy(const rMaterial& material);

protected:
	rTexture* m_diffuseTexture;
	rColor m_diffuseColor;
	rString m_name;
};


inline void rMaterial::SetDiffuseTexture(rTexture* diffuseTexture) {
	m_diffuseTexture = diffuseTexture;
}

inline rTexture* rMaterial::DiffuseTexture() const {
	return m_diffuseTexture;
}

inline void rMaterial::SetDiffuseColor(const rColor& diffuseColor) {
	m_diffuseColor = diffuseColor;
}

inline rColor rMaterial::DiffuseColor() const {
	return m_diffuseColor;
}

inline rString rMaterial::GetName() const {
	return m_name;
}

inline void rMaterial::SetName(const rString& name) {
	m_name = name;
}

#endif
