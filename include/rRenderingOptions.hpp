#pragma once

#include <queue>
#include <stdint.h>

#include "rBuild.hpp"
#include "rColor.hpp"

#include "asset/rMaterial.hpp"



class RECONDITE_API rRenderingOptions{
public:
public:
	rRenderingOptions();
	~rRenderingOptions();
public:

	/**
	Gets the color used for viewport picking.
	\returns viewport picking color.
	*/
	inline rColor PickingColor() const;

	/**
	Sets the visibility state for this object.
	\param visibility new visibility for this object
	*/
	inline void SetVisibility(bool visibility);

	/**
	Gets the visibility state for this object
	\returns the visibility state for this object
	*/
	inline bool GetVisibility() const;

	/**
	Sets whether this object will ignore the depth buffer when rendering.
	\param overdraw value indicating if this object will ignore the depth buffer when rendering.
	*/
	inline void SetOverdraw(bool overdraw);

	/**
	Gets whether this object has overdraw enabled.
	\returns value indicating whether overdraw is enabled.
	*/
	inline bool GetOverdraw() const;

private:

	rColor m_pickingColor;

	bool m_visibility;
	bool m_overdraw;
};

inline rColor rRenderingOptions::PickingColor() const {
	return m_pickingColor;
}

inline void rRenderingOptions::SetVisibility(bool visibility) {
	m_visibility = visibility;
}

inline bool rRenderingOptions::GetVisibility() const {
	return m_visibility;
}

inline void rRenderingOptions::SetOverdraw(bool overdraw) {
	m_overdraw = overdraw;
}

inline bool rRenderingOptions::GetOverdraw() const {
	return m_overdraw;
}