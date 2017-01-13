#include "reToolManager.hpp"
#include "reTools.hpp"

reToolManager::reToolManager(reComponent* component, wxFrame* owner, wxAuiManager* manager){
	m_owner = owner;
	m_component = component;
	m_manager = manager;

	m_activeTool = nullptr;

	m_TransformToolbar = nullptr;

	m_activeToolId = reTOOL_NONE;

	m_component->Bind(reCommandProcessed, this, &reToolManager::OnCommandProcessed);
	m_component->Bind(rEVT_COMPONENT_INITIALIZED, this, &reToolManager::OnComponentInit);

	CreateTools();
}

reToolManager::~reToolManager(){
	Destroy();
}

void reToolManager::CreateTools(){

	m_tools[reTOOL_SELECT] = new reSelectionTool(m_component, m_owner);
	m_tools[reTOOL_TRANSLATE] = new reTranslateTool(m_component, m_owner);
	m_tools[reTOOL_ROTATE] = new reRotateTool(m_component, m_owner);
	m_tools[reTOOL_SCALE] = new reScaleTool(m_component, m_owner);

	ActivateTool(reTOOL_SELECT);
}

void reToolManager::Destroy(){
	for (auto& entry : m_tools){
		delete entry.second;
	}
}

void reToolManager::ActivateTool(reToolId toolId){
	if (toolId == m_activeToolId) return;

	if (m_activeTool){
		m_activeTool->OnDeactivate();
	}

	if (m_tools.count(toolId)){
		m_activeTool = m_tools[toolId];
		m_activeToolId = toolId;

		m_activeTool->OnActivate();
	}
	else{
		m_activeTool = nullptr;
		m_activeToolId = reTOOL_NONE;
	}

	if (m_component->GetViewportManager())
	m_component->GetViewportManager()->UpdateAllViewports(true);
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

bool reToolManager::OnKeyPress(wxKeyEvent& event, rwxGLCanvas* canvas){
	if (m_activeTool)
		return m_activeTool->OnKeyPress(event, canvas);
	else
		return false;
}

void reToolManager::OnCommandProcessed(rEvent& event){
	if (m_activeTool)
		m_activeTool->OnUpdate();
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
		.Top()
		.Position(0)
		.Floatable(false)
		.Gripper(false));


}

void reToolManager::OnComponentInit(rEvent& event) {
	for (auto& tool : m_tools) {
		tool.second->Init();
	}
}


void reToolManager::OnToolbarToolClick(wxCommandEvent& event){
	ActivateTool((reToolId)event.GetId());
}