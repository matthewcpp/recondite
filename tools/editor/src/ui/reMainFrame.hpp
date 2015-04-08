#ifndef RE_MAINFRAME_HPP
#define RE_MAINFRAME_HPP

#include <wx/wx.h>
#include <wx/aui/aui.h>
#include <wx/filedlg.h>
#include <wx/textdlg.h>



#include "reViewportDisplay.hpp"
#include "rePropertyInspector.hpp"
#include "reProjectExplorer.hpp"
#include "reOutliner.hpp"
#include "rePalette.hpp"

#include "project/reComponent.hpp"
#include "tools/reToolManager.hpp"

#include "dialogs/reNewProjectDialog.hpp"


class reMainFrame : public wxFrame{
public:
	reMainFrame(reComponent* component, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
	~reMainFrame();

	void CloseFrame();

private:
	wxMenuBar* CreateEditorMenuBar();
	void CreateUIElements();

private:
	void EnsureViewportDisplayVisible(const wxString& capption = wxEmptyString);
	void ProcessProjectOpen();

private:
	void OnViewWindowSelection(wxCommandEvent& event);

	void OnFileExit(wxCommandEvent& event);

	void NewProject();
	void OpenProject();
	void CloseProject();
	void NewLevel();
	void SaveProject();

	void OnProjectAction(wxCommandEvent& event);

	enum reMainFrameId{
		reMainFrameIdBegin = 20000,

		reMainFrame_ProjectBegin,
		reMainFrame_NewProject,
		reMainFrame_OpenProject,
		reMainFrame_CloseProject,
		reMainFrame_SaveProject,

		reMainFrame_NewLevel,
		reMainFrame_ProjectEnd,

		reMainFrame_IdUIBegin,
		reMainFrame_ViewPropertyInspector,
		reMainFrame_ViewProjectExplorer,
		reMainFrame_ViewOutliner,
		reMainFrame_ViewPalette,
		reMainFrame_IdUIEnd
	};

private:
	reComponent* m_component;

	reViewportDisplay* m_viewportDisplay;
	rePropertyInspector* m_propertyInspector;
	reProjectExplorer* m_projectExplorer;
	reOutliner* m_outliner;
	reToolManager* m_toolManager;
	rePalette* m_palette;

	wxAuiManager m_wxAuiManager;
};

#endif