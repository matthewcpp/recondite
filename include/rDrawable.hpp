#ifndef R_DRAWABLE_HPP
#define R_DRAWABLE_HPP

#include <stdint.h>
#include <queue>

#include "rBuild.hpp"
#include "rDefs.hpp"

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

	rRenderMode RenderMode() const;
	void SetRenderMode(rRenderMode renderMode);

	rColor PickingColor() const;

private:
	rColor m_pickingColor;
	rMaterial* m_material;
	rGeometry* m_geometry;
	bool m_overdraw;
	bool m_visible;
	rRenderMode m_renderMode;

	rPropertyCollection m_materialProperties;

private:
	static PickingColorManager s_drawableIdManager;
};

#endif