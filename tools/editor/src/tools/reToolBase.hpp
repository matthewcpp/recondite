#ifndef RE_TOOLBASE_HPP
#define RE_TOOLBASE_HPP

#include <wx/wx.h>

#include "reTool.hpp"

class reToolBase : public reTool{
public:
	reToolBase(reComponent* component, wxFrame* owner);

public:
	virtual bool OnMouseDown(wxMouseEvent& event, rwxGLCanvas* canvas);
	virtual bool OnMouseUp(wxMouseEvent& event, rwxGLCanvas* canvas);
	virtual bool OnMouseMotion(wxMouseEvent& event, rwxGLCanvas* canvas);

protected:
	bool IsClick();
	void UpdatePoints(wxMouseEvent& event);

protected:
	wxPoint m_firstPoint;
	wxPoint m_previousPoint;
	wxPoint m_currentPoint;
};

#endif