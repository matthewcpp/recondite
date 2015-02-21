#ifndef RE_SELECTIONTOOL_HPP
#define RE_SELECTIONTOOL_HPP

#include "reToolBase.hpp"

class reSelectionTool : public reToolBase{
public:
	reSelectionTool(reComponent* component, wxFrame* owner);

public:
	virtual bool OnMouseUp(wxMouseEvent& event, rwxGLCanvas* canvas);
};

#endif