#ifndef RE_MAINFRAME_HPP
#define RE_MAINFRAME_HPP

#include "wx/wx.h"
#include "wx/aui/aui.h"

#include "rwxComponent.hpp"

#include "reViewportDisplay.hpp"
#include "rePropertyInspector.hpp"
#include "reProjectExplorer.hpp"
#include "reOutliner.hpp"


class reMainFrame : public wxFrame{
public:
	reMainFrame(rwxComponent* component, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
	~reMainFrame();

	void CloseFrame();

private:
	wxMenuBar* CreateEditorMenuBar();

	void OnViewWindowSelection(wxCommandEvent& event);
	void OnFileExit(wxCommandEvent& event);

	enum reMainFrameId{
		reMainFrame_IdUIBegin = 10000,
		reMainFrame_ViewPropertyInspector,
		reMainFrame_ViewProjectExplorer,
		reMainFrame_ViewOutliner,
		reMainFrame_IdUIEnd
	};

private:
	rwxComponent* m_component;

	reViewportDisplay* m_viewportDisplay;
	rePropertyInspector* m_propertyInspector;
	reProjectExplorer* m_projectExplorer;
	reOutliner* m_outliner;

	wxAuiManager m_wxAuiManager;
};

#endif