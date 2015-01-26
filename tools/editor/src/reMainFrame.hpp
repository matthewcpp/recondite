#ifndef RE_MAINFRAME_HPP
#define RE_MAINFRAME_HPP

#include "wx/wx.h"

#include "rwxGLCanvas.hpp"
#include "rwxComponent.hpp"

class reMainFrame : public wxFrame{
public:
	reMainFrame(rwxComponent* component, const wxString& title, const wxPoint& pos, const wxSize& size);

private:
	rwxGLCanvas* m_glCanvas;
	rwxComponent* m_component;
};

#endif