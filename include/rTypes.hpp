#ifndef R_TYPES_HPP
#define R_TYPES_HPP

#include <vector>
#include <map>

#ifdef _RECONDITE_WX_
	#include <wx/wx.h>

	typedef wxString rString;
	typedef wxArrayString rArrayString;
#else
	#include <string>

	typedef std::string rString;
	typedef std::vector<rString> rArrayString;
#endif

typedef std::map<rString,rString> rStringStringMap;
typedef rStringStringMap::iterator rStringStringMapItr;
typedef rStringStringMap::const_iterator rStringStringMapConstItr;
typedef std::pair<rString,rString> rStringStringMapEntry;

#endif
