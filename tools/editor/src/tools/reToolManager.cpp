#include "reToolManager.hpp"

reToolManager::reToolManager(rwxComponent* component, wxFrame* owner, wxAuiManager* manager){
	m_owner = owner;
	m_component = component;
	m_manager = manager;

	m_activeTool = nullptr;

	InitTools();
	CreateToolbars();
}

reToolManager::~reToolManager(){
	Destroy();
}

void reToolManager::InitTools(){
	m_tools[reTOOL_PRIMITIVE_BOX] = new rePrimitiveBoxTool(m_component, m_owner);

	ActivateTool(reTOOL_PRIMITIVE_BOX);
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

void reToolManager::OnMouseDown(wxMouseEvent& event, rwxGLCanvas* canvas){
	if (m_activeTool)
		m_activeTool->OnMouseDown(event, canvas);
}

void reToolManager::OnMouseUp(wxMouseEvent& event, rwxGLCanvas* canvas){
	if (m_activeTool)
		m_activeTool->OnMouseUp(event, canvas);
}

void reToolManager::OnMouseMotion(wxMouseEvent& event, rwxGLCanvas* canvas){
	if (m_activeTool)
		m_activeTool->OnMouseMotion(event, canvas);
}

void reToolManager::CreateToolbars(){
	m_PrimitiveToolbar = new wxAuiToolBar(m_owner);
	m_PrimitiveToolbar->AddTool(reTOOL_PRIMITIVE_BOX, "Primitive Box", wxArtProvider::GetBitmap(wxART_INFORMATION));
	m_PrimitiveToolbar->SetToolBitmapSize(wxSize(16, 16));
	m_PrimitiveToolbar->Realize();

	m_PrimitiveToolbar->Bind(wxEVT_MENU, &reToolManager::OnToolbarToolClick, this);

	m_manager->AddPane(m_PrimitiveToolbar, wxAuiPaneInfo()
		.Name("Primitive Tools")
		.Caption(wxT("Primitive Tools"))
		.ToolbarPane()
		.Top());
}

void reToolManager::OnToolbarToolClick(wxCommandEvent& event){

}