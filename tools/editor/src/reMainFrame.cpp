#include "reMainFrame.hpp"

reMainFrame::reMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	:wxFrame(NULL, wxID_ANY, title, pos, size)
{
	m_glCanvas = new rwxGLCanvas(this);

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(m_glCanvas, 1, wxEXPAND);

	SetSizer(sizer);
}