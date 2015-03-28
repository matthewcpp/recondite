#include "reToolManager.hpp"

reToolManager::reToolManager(reComponent* component, wxFrame* owner, wxAuiManager* manager){
	m_owner = owner;
	m_component = component;
	m_manager = manager;

	m_activeTool = nullptr;

	m_PrimitiveToolbar = nullptr;
	m_TransformToolbar = nullptr;

	InitTools();
}

reToolManager::~reToolManager(){
	Destroy();
}

void reToolManager::InitTools(){
	m_tools[reTOOL_PRIMITIVE_BOX] = new rePrimitiveBoxTool(m_component, m_owner);
	m_tools[reTOOL_PRIMITIVE_GRID] = new rePrimitiveGridTool(m_component, m_owner);
	m_tools[reTOOL_SELECT] = new reSelectionTool(m_component, m_owner);

	ActivateTool(reTOOL_SELECT);
}

void reToolManager::Destroy(){
	for (auto& entry : m_tools){
		delete entry.second;
	}
}

void reToolManager::ActivateTool(reToolId toolId){
	if (m_activeTool)
		m_activeTool->OnDeactivate();

	if (m_tools.count(toolId))
		m_activeTool = m_tools[toolId];
	else
		m_activeTool = nullptr;
}

bool reToolManager::OnMouseDown(wxMouseEvent& event, rwxGLCanvas* canvas){
	if (m_activeTool)
		return m_activeTool->OnMouseDown(event, canvas);
	else
		return false;
}

bool reToolManager::OnMouseUp(wxMouseEvent& event, rwxGLCanvas* canvas){
	if (m_activeTool)
		return m_activeTool->OnMouseUp(event, canvas);
	else
		return false;
}

bool reToolManager::OnMouseMotion(wxMouseEvent& event, rwxGLCanvas* canvas){
	if (m_activeTool)
		return m_activeTool->OnMouseMotion(event, canvas);
	else
		return false;
}

void reToolManager::CreateToolbars(){
	m_TransformToolbar = new wxAuiToolBar(m_owner);
	m_TransformToolbar->SetToolBitmapSize(wxSize(16, 16));
	wxAuiToolBarItem* item = m_TransformToolbar->AddTool(reTOOL_SELECT, "Select", wxBitmap("assets/tool-select.png", wxBITMAP_TYPE_PNG));
	item->SetKind(wxITEM_RADIO);
	item->SetState(wxAUI_BUTTON_STATE_CHECKED);

	m_TransformToolbar->AddTool(reTOOL_TRANSLATE, "Translate", wxBitmap("assets/tool-translate.png", wxBITMAP_TYPE_PNG))->SetKind(wxITEM_RADIO);
	m_TransformToolbar->AddTool(reTOOL_ROTATE, "Rotate", wxBitmap("assets/tool-rotate.png", wxBITMAP_TYPE_PNG))->SetKind(wxITEM_RADIO);
	m_TransformToolbar->AddTool(reTOOL_SCALE, "Scale", wxBitmap("assets/tool-scale.png", wxBITMAP_TYPE_PNG))->SetKind(wxITEM_RADIO);
	m_TransformToolbar->Realize();
	m_TransformToolbar->Bind(wxEVT_MENU, &reToolManager::OnToolbarToolClick, this);
	

	m_manager->AddPane(m_TransformToolbar, wxAuiPaneInfo()
		.Name("Transform Tools")
		.Caption("Transform Tools")
		.ToolbarPane()
		.Top());

	m_PrimitiveToolbar = new wxAuiToolBar(m_owner);
	m_PrimitiveToolbar->SetToolBitmapSize(wxSize(16, 16));
	m_PrimitiveToolbar->AddTool(reTOOL_PRIMITIVE_BOX, "Primitive Box", wxBitmap("assets/tool-box.png", wxBITMAP_TYPE_PNG))->SetKind(wxITEM_RADIO);
	m_PrimitiveToolbar->AddTool(reTOOL_PRIMITIVE_SPHERE, "Primitive Sphere", wxBitmap("assets/tool-sphere.png", wxBITMAP_TYPE_PNG))->SetKind(wxITEM_RADIO);
	m_PrimitiveToolbar->AddTool(reTOOL_PRIMITIVE_CONE, "Primitive Cone", wxBitmap("assets/tool-cone.png", wxBITMAP_TYPE_PNG))->SetKind(wxITEM_RADIO);
	m_PrimitiveToolbar->AddTool(reTOOL_PRIMITIVE_CYLINDER, "Primitive Cylinder", wxBitmap("assets/tool-cylinder.png", wxBITMAP_TYPE_PNG))->SetKind(wxITEM_RADIO);
	m_PrimitiveToolbar->AddTool(reTOOL_PRIMITIVE_GRID, "Primitive Plane", wxBitmap("assets/tool-plane.png", wxBITMAP_TYPE_PNG))->SetKind(wxITEM_RADIO);
	m_PrimitiveToolbar->Realize();
	m_PrimitiveToolbar->Bind(wxEVT_MENU, &reToolManager::OnToolbarToolClick, this);

	m_manager->AddPane(m_PrimitiveToolbar, wxAuiPaneInfo()
		.Name("Primitive Tools")
		.Caption("Primitive Tools")
		.ToolbarPane()
		.Top());
}

void reToolManager::OnToolbarToolClick(wxCommandEvent& event){
	ActivateTool((reToolId)event.GetId());
}