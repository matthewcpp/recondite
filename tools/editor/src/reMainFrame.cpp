#include "reMainFrame.hpp"

reMainFrame::reMainFrame(rwxComponent* component, const wxString& title, const wxPoint& pos, const wxSize& size)
	:wxFrame(NULL, wxID_ANY, title, pos, size)
{
	m_component = component;
	m_wxAuiManager.SetManagedWindow(this);

	m_viewportDisplay = new reViewportDisplay(m_component, this);
	
	SetMenuBar(CreateEditorMenuBar());
	CreateStatusBar();

	m_wxAuiManager.AddPane(m_viewportDisplay, wxCENTER);
	m_wxAuiManager.Update();
}

reMainFrame::~reMainFrame(){
	m_wxAuiManager.UnInit();
}

wxMenuBar* reMainFrame::CreateEditorMenuBar(){
	wxMenuBar* menuBar = new wxMenuBar();

	wxMenu* fileMenu = new wxMenu();
	fileMenu->Append(wxID_EXIT, "Exit\tAlt+F4");
	menuBar->Append(fileMenu, "&File");

	return menuBar;
}