#include "reViewport.hpp"

reViewport::reViewport(rwxComponent* component, reToolManager* toolManager, const wxString& name, wxWindow *parent, wxWindowID id)
	:wxPanel(parent, id)
{
	m_component = component;
	m_toolManager = toolManager;
	m_viewportName = name;

	if (!s_inputTimer) s_inputTimer = new wxTimer();

	CreateViewportElements();
	BindEvents();
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

void reViewport::BindEvents(){
	m_interaction.reset(new rwxViewCameraInteraction(m_glCanvas->GetCamera()));

	m_glCanvas->Bind(wxEVT_LEFT_DOWN, &reViewport::OnCanvasMouseEvent, this);
	m_glCanvas->Bind(wxEVT_LEFT_UP, &reViewport::OnCanvasMouseEvent, this);
	m_glCanvas->Bind(wxEVT_MIDDLE_DOWN, &reViewport::OnCanvasMouseEvent, this);
	m_glCanvas->Bind(wxEVT_MIDDLE_UP, &reViewport::OnCanvasMouseEvent, this);
	m_glCanvas->Bind(wxEVT_RIGHT_DOWN, &reViewport::OnCanvasMouseEvent, this);
	m_glCanvas->Bind(wxEVT_RIGHT_UP, &reViewport::OnCanvasMouseEvent, this);

	m_glCanvas->Bind(wxEVT_MOTION, &reViewport::OnCanvasMouseEvent, this);

	m_glCanvas->Bind(wxEVT_ENTER_WINDOW, &reViewport::OnEnterCanvas, this);

	Bind(wxEVT_TIMER, &reViewport::OnTimer, this);
}

void reViewport::OnCanvasMouseEvent(wxMouseEvent& event){
	wxEventType eventType = event.GetEventType();

	if (eventType == wxEVT_LEFT_DOWN){
		m_toolManager->OnMouseDown(event, m_glCanvas);
	}
	else if (eventType == wxEVT_LEFT_UP){
		m_toolManager->OnMouseUp(event, m_glCanvas);
	}
	else if (eventType == wxEVT_MOTION){
		m_toolManager->OnMouseMotion(event, m_glCanvas);
	}
}

rwxGLCanvas* reViewport::GetCanvas(){
	return m_glCanvas;
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

void reViewport::OnTimer(wxTimerEvent& event){
	if (m_interaction->UpdateKeyboardInteraction())
		m_glCanvas->Refresh();
}

void reViewport::OnEnterCanvas(wxMouseEvent& event){
	s_inputTimer->SetOwner(this);
	s_inputTimer->Start(25);
}

wxTimer* reViewport::s_inputTimer = nullptr;