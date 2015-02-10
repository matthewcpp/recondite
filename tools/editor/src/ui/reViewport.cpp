#include "reViewport.hpp"

reViewport::reViewport(rwxComponent* component, const wxString& name, wxWindow *parent, wxWindowID id)
	:wxPanel(parent, id)
{
	m_component = component;
	m_viewportName = name;

	CreateViewportElements();
}

void reViewport::CreateViewportElements(){
	m_glCanvas = new rwxGLCanvas(m_component, m_viewportName, this);

	m_viewMenuText = new wxStaticText(this, reViewportViewMenuId, "View");
	m_viewMenuText->Bind(wxEVT_LEFT_DOWN, &reViewport::OnViewMenuClick, this);

	m_viewMenu.AppendRadioItem(10000, "Perspective");
	m_viewMenu.AppendRadioItem(10001, "Orthographic");

	m_shadingMenuText = new wxStaticText(this, reViewportShadingMenuId, "Shading");
	m_shadingMenuText->Bind(wxEVT_LEFT_DOWN, &reViewport::OnShadingMenuClick, this);

	m_shadingMenu.AppendRadioItem(10000, "Wireframe");
	m_shadingMenu.AppendRadioItem(10001, "Shaded");
	m_shadingMenu.AppendRadioItem(10002, "Wireframe on Shaded");

	wxBoxSizer* menuSizer = new wxBoxSizer(wxHORIZONTAL);
	menuSizer->Add(m_viewMenuText, 0, wxRIGHT, 3);
	menuSizer->Add(m_shadingMenuText, 0, wxRIGHT, 3);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(menuSizer, 0, wxALL, 3);
	mainSizer->Add(m_glCanvas, 1, wxEXPAND| wxRIGHT|wxLEFT|wxBOTTOM, 3);

	SetSizer(mainSizer);
}

void reViewport::OnViewMenuClick(wxMouseEvent& event){
	m_viewMenuText->GetPopupMenuSelectionFromUser(m_viewMenu);
}

void reViewport::OnShadingMenuClick(wxMouseEvent& event){
	m_shadingMenuText->GetPopupMenuSelectionFromUser(m_shadingMenu);
}

wxString reViewport::GetViewportName(){
	return m_viewportName;
}