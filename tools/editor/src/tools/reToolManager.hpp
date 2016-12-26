#ifndef RE_TOOLMANAGER_HPP
#define RE_TOOLMANAGER_HPP

#include <map>

#include "project/reComponent.hpp"
#include "rwxGLCanvas.hpp"

#include <wx/wx.h>
#include <wx/aui/aui.h>
#include <wx/artprov.h>

#include "reTool.hpp"
#include "reTools.hpp"

class reToolManager{
public:
	reToolManager(reComponent* component, wxFrame* owner, wxAuiManager* manager);
	~reToolManager();

	void CreateToolbars();
	void OnComponentInit(rEvent& event);

public:
	bool OnMouseDown(wxMouseEvent& event, rwxGLCanvas* canvas);
	bool OnMouseUp(wxMouseEvent& event, rwxGLCanvas* canvas);
	bool OnMouseMotion(wxMouseEvent& event, rwxGLCanvas* canvas);

	bool OnKeyDown(wxKeyEvent& event, rwxGLCanvas* canvas);
	bool OnKeyUp(wxKeyEvent& event, rwxGLCanvas* canvas);

	void OnCommandProcessed(rEvent& event);

private:

	void OnToolbarToolClick(wxCommandEvent& event);

	void ActivateTool(reToolId toolId);

	void CreateTools();
	
	void Destroy();

	typedef std::map<reToolId, reTool*> reToolMap;

private:
	reToolMap m_tools;

	wxFrame* m_owner;
	reComponent* m_component;
	wxAuiManager* m_manager;

	reTool* m_activeTool;
	reToolId m_activeToolId;

	wxAuiToolBar* m_TransformToolbar;
};

#endif