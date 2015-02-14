#ifndef RE_TOOLS_HPP
#define RE_TOOLS_HPP

#include "rePrimitiveBoxTool.hpp"

enum reToolId{
	reTOOL_ID_BEGIN = 10000,
	reTOOL_SELECT,
	reTOOL_TRANSLATE,
	reTOOL_ROTATE,
	reTOOL_SCALE,

	reTOOL_PRIMITIVE_BOX,
	reTOOL_PRIMITIVE_SPHERE,
	reTOOL_PRIMITIVE_CONE,
	reTOOL_NONE,
	reTOOL_ID_END
};

#endif