#ifndef RE_TOOLS_HPP
#define RE_TOOLS_HPP

#include "reSelectionTool.hpp"
#include "reTranslateTool.hpp"
#include "reRotateTool.hpp"

enum reToolId{
	reTOOL_ID_BEGIN = 10000,
	reTOOL_NONE,
	reTOOL_SELECT,
	reTOOL_TRANSLATE,
	reTOOL_ROTATE,
	reTOOL_SCALE,

	reTOOL_ID_END
};

#endif