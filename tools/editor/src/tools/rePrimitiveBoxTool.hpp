#ifndef RE_PRIMITIVEBOXTOOL_HPP
#define RE_PRIMITIVEBOXTOOL_HPP

#include "rwxComponent.hpp"

#include <wx/wx.h>

#include "reTool.hpp"

#include "primitive/rPrimitiveBox.hpp"

class rePrimitiveBoxTool : public reTool{
public:
	rePrimitiveBoxTool(rwxComponent* component, wxFrame* owner);

public:

	virtual bool OnMouseDown(wxMouseEvent& event, rwxGLCanvas* canvas);
	virtual bool OnMouseUp(wxMouseEvent& event, rwxGLCanvas* canvas);
	virtual bool OnMouseMotion(wxMouseEvent& event, rwxGLCanvas* canvas);
};

#endif