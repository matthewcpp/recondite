#include "reViewport.hpp"

#include "controllers/reCameraOrientationController.hpp"
#include "controllers/reCameraUserController.hpp"

reViewport::reViewport(reComponent* component, reToolManager* toolManager, reViewportManager* viewportManager, const wxString& name, wxWindow *parent, wxWindowID id)
	:wxPanel(parent, id)
{
	m_component = component;
	m_toolManager = toolManager;
	m_viewportName = name;
	m_viewportManager = viewportManager;

	m_isMaximized = false;

	CreateViewportElements();
	BindEvents();
}

void reViewport::CreateViewportElements(){
	m_glCanvas = new rwxGLCanvas(m_component, m_viewportName, this, s_nextCanvasId++);

	m_viewMenuText = new wxStaticText(this, reViewportViewMenuId, "View");
	m_viewMenuText->Bind(wxEVT_LEFT_DOWN, &reViewport::OnViewMenuClick, this);

	m_viewMenu.AppendRadioItem(10000, "Perspective");
	m_viewMenu.AppendRadioItem(10001, "Orthographic");

	m_shadingMenuText = new wxStaticText(this, reViewportShadingMenuId, "Shading");
	m_shadingMenuText->Bind(wxEVT_LEFT_DOWN, &reViewport::OnShadingMenuClick, this);

	m_shadingMenu.AppendRadioItem(reVIEWPORT_MENU_WIREFRAME, "Wireframe");
	m_shadingMenu.AppendRadioItem(reVIEWPORT_MENU_SHADED, "Shaded")->Check(true);
	m_shadingMenu.AppendRadioItem(reVIEWPORT_MENU_WIREFRAME_ON_SHADED, "Wireframe on Shaded");

	m_minMaxButton = new wxBitmapButton(this, wxID_ANY, wxBitmap("assets/action-maximize.png", wxBITMAP_TYPE_PNG));

	wxBoxSizer* menuSizer = new wxBoxSizer(wxHORIZONTAL);
	menuSizer->Add(m_viewMenuText, 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 3);
	menuSizer->Add(m_shadingMenuText, 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 3);
	menuSizer->AddStretchSpacer();
	menuSizer->Add(m_minMaxButton);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(menuSizer, 0, wxEXPAND|wxALL, 3);
	mainSizer->Add(m_glCanvas, 1, wxEXPAND| wxRIGHT|wxLEFT|wxBOTTOM, 3);


	SetSizer(mainSizer);
}

void reViewport::BindEvents(){
	m_cameraController.reset(new reCameraController(m_glCanvas->GetCamera(), m_component));

	m_glCanvas->Bind(wxEVT_LEFT_DOWN, &reViewport::OnCanvasMouseEvent, this);
	m_glCanvas->Bind(wxEVT_LEFT_UP, &reViewport::OnCanvasMouseEvent, this);
	m_glCanvas->Bind(wxEVT_MIDDLE_DOWN, &reViewport::OnCanvasMouseEvent, this);
	m_glCanvas->Bind(wxEVT_MIDDLE_UP, &reViewport::OnCanvasMouseEvent, this);
	m_glCanvas->Bind(wxEVT_RIGHT_DOWN, &reViewport::OnCanvasMouseEvent, this);
	m_glCanvas->Bind(wxEVT_RIGHT_UP, &reViewport::OnCanvasMouseEvent, this);
	m_glCanvas->Bind(wxEVT_MOUSEWHEEL, &reViewport::OnCanvasMouseEvent, this);
	m_glCanvas->Bind(wxEVT_MOTION, &reViewport::OnCanvasMouseEvent, this);

	this->Bind(wxEVT_KEY_DOWN, &reViewport::OnCanvasKeypress, this);
	m_glCanvas->Bind(wxEVT_KEY_UP, &reViewport::OnCanvasKeypress, this);

	m_minMaxButton->Bind(wxEVT_BUTTON, &reViewport::OnMinMaxButtonPress, this);
}

void reViewport::OnCanvasMouseEvent(wxMouseEvent& event){
	wxEventType eventType = event.GetEventType();

	if (eventType == wxEVT_LEFT_DOWN){
		if (m_toolManager->OnMouseDown(event, m_glCanvas))
			m_viewportManager->UpdateAllViewports();
	}
	else if (eventType == wxEVT_LEFT_UP){
		if(m_toolManager->OnMouseUp(event, m_glCanvas))
			m_viewportManager->UpdateAllViewports();
	}
	else if (eventType == wxEVT_MOTION){
		bool result = m_toolManager->OnMouseMotion(event, m_glCanvas);

		if (result){
			m_viewportManager->UpdateAllViewports();
		}
		else{
			if (m_cameraController->OnMouseMotion(event))
				m_glCanvas->Refresh();
		}
	}
	else if (eventType == wxEVT_MIDDLE_DOWN){
		if (m_cameraController->OnMiddleDown(event))
			m_glCanvas->Refresh();
	}
	else if (eventType == wxEVT_MIDDLE_UP){
		if (m_cameraController->OnMiddleUp(event))
			m_glCanvas->Refresh();
	}
	else if (eventType == wxEVT_RIGHT_DOWN){
		if (m_cameraController->OnRightDown(event))
			m_glCanvas->Refresh();
	}
	else if (eventType == wxEVT_RIGHT_UP){
		if (m_cameraController->OnRightUp(event))
			m_glCanvas->Refresh();
	}
	else if (eventType == wxEVT_MOUSEWHEEL){
		if (m_cameraController->OnMousewheel(event))
			m_glCanvas->Refresh();
	}
}

void reViewport::OnCanvasKeypress(wxKeyEvent& event){
	wxEventType eventType = event.GetEventType();

	bool handled = false;

	if (eventType == wxEVT_KEY_DOWN)
		handled = m_toolManager->OnKeyDown(event, m_glCanvas);
	else
		handled = m_toolManager->OnKeyUp(event, m_glCanvas);

	if (!handled){
		event.Skip();
	}
}

rwxGLCanvas* reViewport::GetCanvas(){
	return m_glCanvas;
}

void reViewport::OnViewMenuClick(wxMouseEvent& event){
	m_viewMenuText->GetPopupMenuSelectionFromUser(m_viewMenu);
}

void reViewport::SetRenderMode(rRenderMode renderMode) {
	m_glCanvas->GetViewport()->SetRenderMode(renderMode);
	Refresh();
}

void reViewport::OnShadingMenuClick(wxMouseEvent& event){
	int shadingMenuChoice = m_shadingMenuText->GetPopupMenuSelectionFromUser(m_shadingMenu);
	
	switch (shadingMenuChoice){
	case reVIEWPORT_MENU_WIREFRAME:
		SetRenderMode(rRenderMode::Wireframe);
		break;

	case reVIEWPORT_MENU_SHADED:
		SetRenderMode(rRenderMode::Shaded);
		break;

	case reVIEWPORT_MENU_WIREFRAME_ON_SHADED:
		SetRenderMode(rRenderMode::WireframeOnShaded);
		break;
	}
}

wxString reViewport::GetViewportName(){
	return m_viewportName;
}

void reViewport::OnMinMaxButtonPress(wxCommandEvent& event){
	if (m_isMaximized){
		m_viewportManager->RestoreViewports();
		SetViewportIsMaximized(false);
	}
	else{
		m_viewportManager->MaximizeViewport(m_glCanvas->GetId());
		SetViewportIsMaximized(true);
	}
	
}

void reViewport::SetViewportIsMaximized(bool maximized){
	if (maximized)
		m_minMaxButton->SetBitmap(wxBitmap("assets/action-minimize.png", wxBITMAP_TYPE_PNG));
	else
		m_minMaxButton->SetBitmap(wxBitmap("assets/action-maximize.png", wxBITMAP_TYPE_PNG));

	m_isMaximized = maximized;
}

void reViewport::SetViewOrientation(reViewOrientation viewOrientation) {
	rAlignedBox3 sceneBounding = m_component->GetScene()->GetBounding();
	SetViewOrientation(viewOrientation, sceneBounding);
}

void reViewport::SetViewOrientation(reViewOrientation viewOrientation, const rAlignedBox3& bounding) {
	rVector3 center = bounding.Center();
	float distance = bounding.max.Distance(bounding.min) / 2;
	
	
	recondite::Camera* camera = m_glCanvas->GetCamera();
	rVector3 position;
	rVector3 up = rVector3::UpVector;
	rVector3 target = center;

	switch (viewOrientation) {
	case reViewOrientation::Top: 
		position.Set(center.x, bounding.max.y + distance, center.z);
		up = rVector3::RightVector;
		break;

		case reViewOrientation::Bottom:
			position.Set(center.x, bounding.min.y - distance, center.z);
			up = rVector3::RightVector;
			break;

		case reViewOrientation::Right:
			position.Set(bounding.max.x + distance, center.y, center.z);
			break;

		case reViewOrientation::Left:
			position.Set(bounding.min.x - distance, center.y, center.z);
			break;

		case reViewOrientation::Front:
			position.Set(center.x, center.y, bounding.max.z + distance);
			break;

		case reViewOrientation::Back:
			position.Set(center.x, center.y, bounding.min.z - distance);
			break;

		case reViewOrientation::User: {
			position = bounding.max;
			rVector3 forward = target - position;
			forward.Normalize();
			rVector3 right = forward.Cross(up);
			up = right.Cross(forward);
			break;
		}
	};

	camera->SetPosition(position);
	camera->SetTarget(target);
	camera->SetUp(up);

	if (viewOrientation != reViewOrientation::User)
		m_cameraController.reset(new reCameraOrientationController(viewOrientation, m_glCanvas->GetCamera(), m_component));
	else
		m_cameraController.reset(new reCameraUserController(m_glCanvas->GetCamera(), m_component));
}

wxWindowID reViewport::s_nextCanvasId = 17000;