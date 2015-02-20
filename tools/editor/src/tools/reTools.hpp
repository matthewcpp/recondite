#ifndef RE_TOOLS_HPP
#define RE_TOOLS_HPP

#include "rePrimitiveBoxTool.hpp"
#include "reSelectionTool.hpp"

enum reToolId{
	reTOOL_ID_BEGIN = 10000,
	reTOOL_SELECT,
	reTOOL_TRANSLATE,
	reTOOL_ROTATE,
	reTOOL_SCALE,

	reTOOL_PRIMITIVE_BOX,
	reTOOL_PRIMITIVE_SPHERE,
	reTOOL_PRIMITIVE_CONE,
	reTOOL_PRIMITIVE_CYLINDER,
	reTOOL_PRIMITIVE_PLANE,
	reTOOL_NONE,
	reTOOL_ID_END
};

#endif