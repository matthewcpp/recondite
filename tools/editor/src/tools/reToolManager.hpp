#ifndef RE_TOOLMANAGER_HPP
#define RE_TOOLMANAGER_HPP

#include <map>

#include "rwxComponent.hpp"
#include "rwxGLCanvas.hpp"

#include <wx/wx.h>
#include <wx/aui/aui.h>
#include <wx/artprov.h>



#include "reTool.hpp"
#include "reTools.hpp"

class reToolManager{
public:
	reToolManager(rwxComponent* component, wxFrame* owner, wxAuiManager* manager);
	~reToolManager();

public:
	void OnMouseDown(wxMouseEvent& event, rwxGLCanvas* canvas);
	void OnMouseUp(wxMouseEvent& event, rwxGLCanvas* canvas);
	void OnMouseMotion(wxMouseEvent& event, rwxGLCanvas* canvas);

private:

	void OnToolbarToolClick(wxCommandEvent& event);

	void ActivateTool(reToolId toolId);

	void InitTools();
	void CreateToolbars();
	void Destroy();

	typedef std::map<reToolId, reTool*> reToolMap;

private:
	reToolMap m_tools;

	wxFrame* m_owner;
	rwxComponent* m_component;
	wxAuiManager* m_manager;

	reTool* m_activeTool;

	wxAuiToolBar* m_PrimitiveToolbar;
};

#endif