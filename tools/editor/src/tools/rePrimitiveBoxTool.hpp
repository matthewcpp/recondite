#ifndef RE_PRIMITIVEBOXTOOL_HPP
#define RE_PRIMITIVEBOXTOOL_HPP

#include "rwxComponent.hpp"

#include <wx/wx.h>

#include "reToolBase.hpp"

#include "primitive/rPrimitiveBox.hpp"

class rePrimitiveBoxTool : public reToolBase{
public:
	rePrimitiveBoxTool(reComponent* component, wxFrame* owner);

public:

	virtual bool OnMouseUp(wxMouseEvent& event, rwxGLCanvas* canvas);
};

#endif