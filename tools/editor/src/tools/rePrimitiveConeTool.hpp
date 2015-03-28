#ifndef RE_PRIMITIVECONETOOL_HPP
#define RE_PRIMITIVECONETOOL_HPP

#include "rwxComponent.hpp"

#include <wx/wx.h>

#include "reToolBase.hpp"

#include "primitive/rPrimitiveCone.hpp"

class rePrimitiveConeTool : public reToolBase{
public:
	rePrimitiveConeTool(reComponent* component, wxFrame* owner);

public:

	virtual bool OnMouseUp(wxMouseEvent& event, rwxGLCanvas* canvas);
};

#endif