#ifndef R_TYPES_HPP
#define R_TYPES_HPP

#include <vector>
#include <map>

#include "rVector2.hpp"
#include "rVector3.hpp"
#include "rString.hpp"
#include "rArrayString.hpp"

typedef std::map<rString,rString> rStringStringMap;

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
#endif
