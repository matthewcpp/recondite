#pragma once

#include <queue>
#include <stdint.h>

#include "rBuild.hpp"
#include "rColor.hpp"

#include "asset/rMaterial.hpp"



class RECONDITE_API rRenderingOptions{
public:
	rRenderingOptions() : m_visibility(true), m_layer(0) {}

public:

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

	inline uint32_t GetLayer() const;
	inline void SetLayer(uint32_t layer);

private:

	bool m_visibility;
	uint32_t m_layer;
};


inline void rRenderingOptions::SetVisibility(bool visibility) {
	m_visibility = visibility;
}

inline bool rRenderingOptions::GetVisibility() const {
	return m_visibility;
}

inline uint32_t rRenderingOptions::GetLayer() const {
	return m_layer;
}

inline void rRenderingOptions::SetLayer(uint32_t layer) {
	m_layer = layer;
}
