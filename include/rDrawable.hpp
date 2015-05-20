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

	bool Visible() const;
	void SetVisibility(bool visibility);

	bool ForceRender();
	void SetForceRender(bool forceRender);

	rShader* Shader() const;
	void SetShader(rShader* shader);


	rColor PickingColor() const;

private:
	rColor m_pickingColor;
	bool m_visible;
	bool m_forceRender;
	rShader* m_shader;

private:
	static PickingColorManager s_drawableIdManager;
};

#endif