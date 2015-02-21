#ifndef RE_TOOL_HPP
#define RE_TOOL_HPP

#include "project/reComponent.hpp"

#include "rwxGLCanvas.hpp"

#include <wx/wx.h>

class reTool{
public:
	reTool(reComponent* component, wxFrame* owner) :m_owner(owner), m_component(component) {}

public:
	virtual bool OnMouseDown(wxMouseEvent& event, rwxGLCanvas* canvas) { return false; }
	virtual bool OnMouseUp(wxMouseEvent& event, rwxGLCanvas* canvas) { return false; }
	virtual bool OnMouseMotion(wxMouseEvent& event, rwxGLCanvas* canvas) { return false; }

	virtual void OnActivate() {}
	virtual void OnDeactivate() {}

protected:
	wxFrame* m_owner;
	reComponent* m_component;

rNO_COPY_CLASS(reTool)
};

#endif