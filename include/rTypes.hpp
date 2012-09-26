#ifndef R_TYPES_HPP
#define R_TYPES_HPP

#include <vector>

#ifdef _RECONDITE_WX_
	#include <wx/wx.h>

	typedef wxString rString;
	typedef wxColor rColor;
	typedef wxArrayString rArrayString;
#else
	#include <string>
	#include "rColor.hpp"

	typedef std::string rString;
	typedef rColour rColor;
	typedef std::vector<rString> rArrayString;
#endif

typedef std::vector<int> rIntArray;
typedef std::vector<float> rFloatArray;

#endif