#ifndef RE_VIEWPORT_HPP
#define RE_VIEWPORT_HPP

#include "project/reComponent.hpp"

#include "rwxGLCanvas.hpp"
#include <wx/wx.h>
#include <wx/timer.h>

#include "tools/reToolManager.hpp"
#include "rwxViewCameraInteraction.hpp"

class reViewportManager {
public:
	virtual void UpdateAllViewports() = 0;
};

class reViewport : public wxPanel{
public:
	reViewport(reComponent* component, reToolManager* toolManager, reViewportManager* viewportManager, const wxString& name, wxWindow *parent, wxWindowID id = wxID_ANY);

public:
	wxString GetViewportName();
	rwxGLCanvas* GetCanvas();

private:
	void CreateViewportElements();
	void BindEvents();

private:
	void OnViewMenuClick(wxMouseEvent& event);
	void OnShadingMenuClick(wxMouseEvent& event);

	void OnCanvasMouseEvent(wxMouseEvent& event);

	void OnEnterCanvas(wxMouseEvent& event);
	void OnTimer(wxTimerEvent& event);

private:

	enum reViewportId{
		reViewportViewMenuId = 10000,
		reViewportShadingMenuId
	};

private:
	rwxGLCanvas* m_glCanvas;
	reComponent* m_component;
	reToolManager* m_toolManager;
	reViewportManager* m_viewportManager;

	wxStaticText* m_viewMenuText;
	wxMenu m_viewMenu;

	wxStaticText* m_shadingMenuText;
	wxMenu m_shadingMenu;

	wxString m_viewportName;

	static wxTimer* s_inputTimer;
	static wxWindowID s_nextCanvasId;

	std::unique_ptr<rwxViewCameraInteraction> m_interaction;
};

#endif