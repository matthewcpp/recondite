#ifndef RE_MAINFRAME_HPP
#define RE_MAINFRAME_HPP

#include "wx/wx.h"
#include "wx/aui/aui.h"

#include "reViewportDisplay.hpp"
#include "rwxComponent.hpp"

class reMainFrame : public wxFrame{
public:
	reMainFrame(rwxComponent* component, const wxString& title, const wxPoint& pos, const wxSize& size);
	~reMainFrame();

private:
	wxMenuBar* CreateEditorMenuBar();

private:
	reViewportDisplay* m_viewportDisplay;
	rwxComponent* m_component;

	wxAuiManager m_wxAuiManager;
};

#endif