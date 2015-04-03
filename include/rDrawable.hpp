#ifndef R_DRAWABLE_HPP
#define R_DRAWABLE_HPP

#include <stdint.h>
#include <queue>

#include "rBuild.hpp"

#include "rColor.hpp"
#include "rPropertyCollection.hpp"

#include "rMaterial.hpp"
#include "rGeometry.hpp"

class RECONDITE_API PickingColorManager{
public:
	PickingColorManager() : r(0), g(0), b(0), a(UINT8_MAX) {}

	bool GetNextColor(rColor& color);
	void ReturnColor(const rColor& color);

private:
	typedef std::queue<rColor> PickingColorQueue;

private:
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	PickingColorQueue m_availableColors;
};

class RECONDITE_API rDrawable{
public:
	rDrawable();
	~rDrawable();

public:

	rMaterial* Material() const;
	void SetMaterial(rMaterial* material);

	rGeometry* Geometry() const;
	void SetGeometry(rGeometry* geometry);

	rPropertyCollection& MaterialProperties();

	bool Visible() const;
	void SetVisibility(bool visibility);

	rColor PickingColor() const;

	bool FaceVisibility() const;
	void SetFaceVisibility(bool visibility);

	bool LineVisibility() const;
	void SetLineVisibility(bool visibility);

private:
	rColor m_pickingColor;
	rMaterial* m_material;
	rGeometry* m_geometry;
	bool m_visible;
	bool m_lineVisibility;
	bool m_faceVisibility;

	rPropertyCollection m_materialProperties;

private:
	static PickingColorManager s_drawableIdManager;
};

#endif