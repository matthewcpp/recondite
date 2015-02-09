#ifndef RE_VIEWPORT_HPP
#define RE_VIEWPORT_HPP

#include "rwxComponent.hpp"

#include "rwxGLCanvas.hpp"
#include "wx/wx.h"

class reViewport : public wxPanel{
public:
	reViewport(rwxComponent* component, const wxString& name, wxWindow *parent, wxWindowID id = wxID_ANY);

public:
	wxString GetViewportName();

private:
	void CreateViewportElements();

private:
	void OnViewMenuClick(wxMouseEvent& event);
	void OnShadingMenuClick(wxMouseEvent& event);

private:

	enum reViewportId{
		reViewportViewMenuId = 10000,
		reViewportShadingMenuId
	};

private:
	rwxGLCanvas* m_glCanvas;
	rwxComponent* m_component;

	wxStaticText* m_viewMenuText;
	wxMenu m_viewMenu;

	wxStaticText* m_shadingMenuText;
	wxMenu m_shadingMenu;

	wxString m_viewportName;
};

#endif