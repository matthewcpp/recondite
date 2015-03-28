#ifndef RE_PRIMITIVEGRIDTOOL_HPP
#define RE_PRIMITIVEGRIDTOOL_HPP

#include "rwxComponent.hpp"

#include <wx/wx.h>

#include "reToolBase.hpp"

#include "primitive/rPrimitiveGrid.hpp"

class rePrimitiveGridTool : public reToolBase{
public:
	rePrimitiveGridTool(reComponent* component, wxFrame* owner);

public:
	virtual bool OnMouseUp(wxMouseEvent& event, rwxGLCanvas* canvas) override;
};

#endif