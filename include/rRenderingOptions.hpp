#pragma once

#include <queue>
#include <stdint.h>

#include "rBuild.hpp"
#include "rColor.hpp"

#include "asset/rMaterial.hpp"



class RECONDITE_API rRenderingOptions{
public:
	rRenderingOptions() : m_visibility(true) {}

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


private:

	bool m_visibility;
};


inline void rRenderingOptions::SetVisibility(bool visibility) {
	m_visibility = visibility;
}

inline bool rRenderingOptions::GetVisibility() const {
	return m_visibility;
}
