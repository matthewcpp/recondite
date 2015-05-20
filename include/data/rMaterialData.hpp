#ifndef R_MATERIAL_DATA_HPP
#define R_MATERIAL_DATA_HPP

#include <map>
#include <fstream>

#include "rBuild.hpp"
#include "rTypes.hpp"
#include "rString.hpp"
#include "rColor.hpp"

class RECONDITE_API rMaterialData{
public:
	rMaterialData();

	rString Name() const;
	void SetName(const rString& name);

	rString DiffuseTextureName() const;
	void SetDiffuseTextureName(const rString& name);

	rColor DiffuseColor() const;
	void SetDiffuseColor(const rColor& color);

private:
	rString m_name;
	rString m_diffuseTetureName;
	rColor m_diffuseColor;
};

#endif
