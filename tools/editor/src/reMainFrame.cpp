#include "reMainFrame.hpp"

reMainFrame::reMainFrame(rwxComponent* component, const wxString& title, const wxPoint& pos, const wxSize& size)
	:wxFrame(NULL, wxID_ANY, title, pos, size)
{
	m_component = component;
	m_glCanvas = new rwxGLCanvas(m_component, this);

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(m_glCanvas, 1, wxEXPAND);

	SetSizer(sizer);
}