#ifndef R_DEFS_HPP
#define R_DEFS_HPP

#include <vector>
#include <map>
#include <string>

#include "rVector2.hpp"
#include "rVector3.hpp"

#include "rColor.hpp"

typedef std::string rString;

typedef std::vector<int> rIntArray;
typedef std::vector<float> rFloatArray;
typedef std::vector<char> rCharArray;
typedef std::vector<unsigned char> rUnsigedByteArray;
typedef std::vector<unsigned short> rUnsignedShortArray;

typedef std::vector<rVector2> rVector2Array;
typedef std::vector<rVector3> rVector3Array;

typedef rVector2Array rVertex2Array;
typedef rVector3Array  rVertex3Array;
typedef std::vector<unsigned short> rIndexArray;

typedef std::map<rString, rColor> rColorMap;
typedef rColorMap::iterator rColorItr;
typedef rColorMap::const_iterator rColorConstItr;
typedef std::pair<rString, rColor> rColorMapEntry;

enum rContentError{
	rCONTENT_ERROR_NONE = 0,
	rCONTENT_ERROR_FILE_NOT_FOUND,
	rCONTENT_ERROR_FILE_NOT_READABLE,
        rCONTENT_ERROR_FILE_NOT_WRITABLE,
	
	rCONTENT_ERROR_ASSET_NOT_PRESENT,
	rCONTENT_ERROR_ASSET_NAME_ALREADY_PRESENT,
	rCONTENT_ERROR_ASSET_IN_USE,
	rCONTENT_ERROR_UNABLE_TO_LOAD_DEPENDENCY,
	
	rCONTENT_ERROR_PARSE_ERROR,
	rCONTENT_ERROR_UNKNOWN_ASSET_TYPE,
	rCONTENT_ERROR_STREAM_ERROR
};

enum rAssetType{
	rASSET_TEXTURE2D = 0,
	rASSET_SHADER,
	rASSET_MATERIAL,
	rASSET_GEOMETRY,
	rASSET_FONT,
	rASSET_MODEL,
	rASSET_SOUND,
	rASSET_NUM_TYPES,
	rASSET_UNKNOWN
};

enum rAssetSource{
	rASSET_SOURCE_FILE,
	rASSET_SOURCE_RESOURCE,
	rASSET_SOURCE_INTERNAL
};

enum rMaterialParameterType{
	rMATERIAL_PARAMETER_INT,
	rMATERIAL_PARAMETER_FLOAT,
	rMATERIAL_PARAMETER_VEC3,
	rMATERIAL_PARAMETER_MATRIX4,
	rMATERIAL_PARAMETER_TEXTURE2D,
	rMATERIAL_PARAMETER_COLOR,
	
	rMATERIAL_PARAMETER_UNKNOWN
};

enum rGeometryType{
	rGEOMETRY_TRIANGLES,
	rGEOMETRY_LINES,
};

#endif
