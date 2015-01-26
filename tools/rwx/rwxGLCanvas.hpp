#ifndef RWX_GLCANVAS_HPP
#define RWX_GLCANVAS_HPP

//note this must be included before GL canvas because glew.h must be included before gl.h
#include "rwxComponent.hpp"

#include "wx/wx.h"
#include "wx/glcanvas.h"

#include "rBuild.hpp"

class RECONDITE_RWX_CLASS rwxGLCanvas : public wxGLCanvas{
public:
	rwxGLCanvas(rwxComponent* component, wxWindow *parent, wxWindowID id = wxID_ANY);
	void OnPaint(wxPaintEvent& event);

private:
	rwxComponent* m_component;
};

#endif