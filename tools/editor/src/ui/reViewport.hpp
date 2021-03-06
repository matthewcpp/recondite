#ifndef RE_VIEWPORT_HPP
#define RE_VIEWPORT_HPP

#include <memory>

#include "project/reComponent.hpp"

#include "rwxGLCanvas.hpp"
#include <wx/wx.h>
#include <wx/timer.h>

#include "tools/reToolManager.hpp"

#include "controllers/reCameraController.hpp"

enum reViewportMenuId{
	reVIEWPORT_MENU_WIREFRAME = 10000,
	reVIEWPORT_MENU_SHADED,
	reVIEWPORT_MENU_WIREFRAME_ON_SHADED,

	reVIEWPORT_MENU_PERSPECTIVE,
	reVIEWPORT_MENU_ORTHOGRAPHIC,

	reVIEWPORT_MENU_USER,
	reVIEWPORT_MENU_TOP,
	reVIEWPORT_MENU_BOTTOM,
	reVIEWPORT_MENU_LEFT,
	reVIEWPORT_MENU_RIGHT,
	reVIEWPORT_MENU_FRONT,
	reVIEWPORT_MENU_BACK
};

class reViewport : public wxPanel{
public:
	reViewport(reComponent* component, reToolManager* toolManager, reViewportManager* viewportManager, const wxString& name, wxWindow *parent, wxWindowID id = wxID_ANY);

public:
	wxString GetViewportName();

	void SetViewportIsMaximized(bool maximized);

	rwxGLCanvas* GetCanvas();

	void SetViewOrientation(reViewOrientation viewOrientation, bool updateMenu = true);
	void SetViewOrientation(reViewOrientation viewOrientation, const rAlignedBox3& bounding, bool updateMenu = true);
	void SetRenderMode(rRenderMode renderMode);
	void SetProjection(rViewportType viewportType);

private:
	void CreateViewportElements();
	void BindEvents();

private:
	void OnViewMenuClick(wxMouseEvent& event);
	void OnShadingMenuClick(wxMouseEvent& event);
	void OnMinMaxButtonPress(wxCommandEvent& event);

	void OnCanvasMouseEvent(wxMouseEvent& event);

	void OnMouseEnter(wxMouseEvent& event);
	void OnMouseLeave(wxMouseEvent& event);

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

	wxBitmapButton* m_minMaxButton;
	bool m_isMaximized;

	wxString m_viewportName;

	static wxWindowID s_nextCanvasId;

	std::unique_ptr<reCameraController> m_cameraController;
};

#endif