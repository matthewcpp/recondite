#ifndef R_RENDERINGOPTIONS_HPP
#define R_RENDERINGOPTIONS_HPP

#include <queue>
#include <stdint.h>

#include "rBuild.hpp"
#include "rColor.hpp"

class RECONDITE_API rPickingColorManager{
public:
	rPickingColorManager() : r(0), g(0), b(0), a(UINT8_MAX) {}

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

class RECONDITE_API rRenderingOptions{
public:
	rRenderingOptions();
	virtual ~rRenderingOptions();

public:
	bool ForceRender() const;
	void SetForceRender(bool forceRender);

	bool Visible() const;
	void SetVisibility(bool visible);

	bool Overdraw() const;
	void SetOverdraw(bool overdraw);

	rColor PickingColor() const;

private:
	bool m_forceRender;
	bool m_overdraw;
	bool m_visibility;

	rColor m_pickingColor;

	static rPickingColorManager s_pickingColorManager;
};

#endif