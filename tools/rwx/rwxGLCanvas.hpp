#ifndef RWX_GLCANVAS_HPP
#define RWX_GLCANVAS_HPP

#include "wx/wx.h"
#include "wx/glcanvas.h"

#include "rBuild.hpp"

class RECONDITE_RWX_CLASS rwxGLCanvas : public wxGLCanvas{
public:
	rwxGLCanvas(wxWindow *parent, wxWindowID id = wxID_ANY);
	void OnPaint(wxPaintEvent& event);

private:
	wxGLContext* glContext;
};

#endif