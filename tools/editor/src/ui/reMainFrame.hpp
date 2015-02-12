#ifndef RE_MAINFRAME_HPP
#define RE_MAINFRAME_HPP

#include <wx/wx.h>
#include <wx/aui/aui.h>
#include <wx/filedlg.h>
#include <wx/textdlg.h>

#include "rwxComponent.hpp"

#include "reViewportDisplay.hpp"
#include "rePropertyInspector.hpp"
#include "reProjectExplorer.hpp"
#include "reOutliner.hpp"

#include "project/reProject.hpp"

#include "tools/reToolManager.hpp"

#include "dialogs/reNewProjectDialog.hpp"


class reMainFrame : public wxFrame{
public:
	reMainFrame(rwxComponent* component, reProject* project, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
	~reMainFrame();

	void CloseFrame();

private:
	wxMenuBar* CreateEditorMenuBar();

private:
	void EnsureViewportDisplayVisible(const wxString& capption = wxEmptyString);
	void ProcessProjectOpen();

private:
	void OnViewWindowSelection(wxCommandEvent& event);

	void OnFileExit(wxCommandEvent& event);

	void OnNewProject(wxCommandEvent& event);
	void OnNewLevel(wxCommandEvent& event);
	void OnOpenProject(wxCommandEvent& event);
	void OnCloseProject(wxCommandEvent& event);

	enum reMainFrameId{
		reMainFrameIdBegin = 20000,

		reMainFrame_MenuNewProject,
		reMainFrame_MenuOpenProject,
		reMainFrame_MenuCloseProject,

		reMainFrame_MenuNewLevel,

		reMainFrame_IdUIBegin,
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
	reToolManager* m_toolManager;

	reProject* m_project;

	wxAuiManager m_wxAuiManager;
};

#endif