#ifndef R_DEFS_HPP
#define R_DEFS_HPP

#include <vector>

#include "rVector2.hpp"
#include "rVector3.hpp"

typedef std::vector<unsigned char> rUnsigedByteArray;
typedef std::vector<unsigned short> rUnsignedShortArray;

typedef std::vector<rVector2> rVector2Array;
typedef std::vector<rVector3> rVector3Array;

enum rContentError{
	rCONTENT_ERROR_NONE = 0,
	rCONTENT_ERROR_FILE_NOT_FOUND,
	rCONTENT_ERROR_FILE_NOT_READABLE,
	
	rCONTENT_ERROR_RESOURCE_NOT_PRESENT
};

enum rAssetType{
	rASSET_TEXTURE2D = 0,
	rASSET_MATERIAL,
	rASSET_MODEL,
	rASSET_SOUND
};

enum rAssetSource{
	rASSET_SOURCE_FILE,
	rASSET_SOURCE_RESOURCE,
	rASSET_SOURCE_INTERNAL
};

#endif