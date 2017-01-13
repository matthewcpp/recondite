#include "reViewportDisplay.hpp"

reViewportDisplay::reViewportDisplay(reComponent* component, reToolManager* toolManager, wxWindow* parent, wxWindowID id)
	:wxPanel(parent, id)
{
	m_component = component;
	m_toolManager = toolManager;

	m_activeViewport = nullptr;

	CreateViewportDisplay();

	m_component->Bind(rEVT_COMPONENT_INITIALIZED, this, &reViewportDisplay::OnComponentInitialized);

	m_isMaximized = false;
	m_hoverCanvas = nullptr;
	m_lastUpdateTime = 0;
}

reViewport* reViewportDisplay::GetActiveViewport(){
	return m_activeViewport;
}

void reViewportDisplay::OnViewportActivate(wxMouseEvent& event){
	int id = event.GetId();

	if (id == m_topLeftViewport->GetCanvas()->GetId())
		m_activeViewport = m_topLeftViewport;

	else if (id == m_topRightViewport->GetCanvas()->GetId())
		m_activeViewport = m_topRightViewport;

	else if (id == m_bottomLeftViewport->GetCanvas()->GetId())
		m_activeViewport = m_bottomLeftViewport;

	else if (id == m_bottomRightViewport->GetCanvas()->GetId())
		m_activeViewport = m_bottomRightViewport;

	else
		m_activeViewport = nullptr;

	event.Skip();
}

void reViewportDisplay::BindCanvasEvents(rwxGLCanvas* canvas){
	canvas->Bind(wxEVT_LEFT_DOWN, &reViewportDisplay::OnViewportActivate, this);
	canvas->Bind(wxEVT_MIDDLE_DOWN, &reViewportDisplay::OnViewportActivate, this);
	canvas->Bind(wxEVT_RIGHT_DOWN, &reViewportDisplay::OnViewportActivate, this);

	canvas->SetDropTarget(new rePaletteDropTarget(m_component, canvas));
}

void reViewportDisplay::CreateViewportDisplay(){
	m_mainSplitter = new wxSplitterWindow(this, wxID_ANY);
	m_mainSplitter->SetSashGravity(0.5);

	m_leftSplitter = new wxSplitterWindow(m_mainSplitter, wxID_ANY);
	m_leftSplitter->SetSashGravity(0.5);

	m_topLeftViewport = new reViewport(m_component, m_toolManager, this, "Viewport 1", m_leftSplitter);
	m_bottomLeftViewport = new reViewport(m_component, m_toolManager, this, "Viewport 2", m_leftSplitter);
	m_leftSplitter->SplitHorizontally(m_topLeftViewport, m_bottomLeftViewport);

	m_rightSplitter = new wxSplitterWindow(m_mainSplitter, wxID_ANY);
	m_rightSplitter->SetSashGravity(0.5);

	m_topRightViewport = new reViewport(m_component, m_toolManager, this, "Viewport 3", m_rightSplitter);
	m_bottomRightViewport = new reViewport(m_component, m_toolManager, this, "Viewport 4", m_rightSplitter);
	m_rightSplitter->SplitHorizontally(m_topRightViewport, m_bottomRightViewport);

	m_mainSplitter->SplitVertically(m_leftSplitter, m_rightSplitter);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(m_mainSplitter, 1, wxEXPAND | wxALL, 2);
	SetSizer(mainSizer);
}

reViewport* reViewportDisplay::GetViewport(const wxString& name){
	if (name == m_topLeftViewport->GetViewportName())
		return m_topLeftViewport;
	else if (name == m_topRightViewport->GetViewportName())
		return m_topRightViewport;
	else if (name == m_bottomLeftViewport->GetViewportName())
		return m_bottomLeftViewport;
	else if (name == m_bottomRightViewport->GetViewportName())
		return m_bottomRightViewport;
	else
		return nullptr;
}

void reViewportDisplay::OnComponentInitialized(rEvent& event){
	rScene* scene = m_component->GetScene();

	scene->Bind(rEVT_SCENE_ACTOR_ADDED, this, &reViewportDisplay::OnDisplayShouldUpdate);
	scene->Bind(rEVT_SCENE_ACTOR_REMOVED, this, &reViewportDisplay::OnDisplayShouldUpdate);
	scene->Bind(rEVT_SCENE_LOAD_END, this, &reViewportDisplay::OnSceneLoadComplete);

	m_component->Bind(reCommandProcessed, this, &reViewportDisplay::OnCommandProcessed);

	BindCanvasEvents(m_topLeftViewport->GetCanvas());
	BindCanvasEvents(m_topRightViewport->GetCanvas());
	BindCanvasEvents(m_bottomLeftViewport->GetCanvas());
	BindCanvasEvents(m_bottomRightViewport->GetCanvas());
}

void reViewportDisplay::SetDefaultViewOrientations() {
	rAlignedBox3 bounding = m_component->GetScene()->GetBounding();
	m_topLeftViewport->SetViewOrientation(reViewOrientation::User, bounding);

	m_topRightViewport->SetViewOrientation(reViewOrientation::Top, bounding);
	m_topRightViewport->SetRenderMode(rRenderMode::Wireframe);
	m_topRightViewport->SetProjection(rViewportType::rVIEWPORT_ORTHO);

	m_bottomLeftViewport->SetViewOrientation(reViewOrientation::Right, bounding);
	m_bottomLeftViewport->SetRenderMode(rRenderMode::Wireframe);
	m_bottomLeftViewport->SetProjection(rViewportType::rVIEWPORT_ORTHO);

	m_bottomRightViewport->SetViewOrientation(reViewOrientation::Front, bounding);
	m_bottomRightViewport->SetRenderMode(rRenderMode::Wireframe);
	m_bottomRightViewport->SetProjection(rViewportType::rVIEWPORT_ORTHO);
}

void reViewportDisplay::OnSceneLoadComplete(rEvent& event) {
	SetDefaultViewOrientations();
	UpdateAllViewports();
}

void reViewportDisplay::UpdateAllViewports(bool force){
	wxLongLong updateTime = wxGetUTCTimeMillis();

	if ((updateTime - m_lastUpdateTime > 33) || force) {
		m_topLeftViewport->GetCanvas()->Refresh();
		m_topRightViewport->GetCanvas()->Refresh();
		m_bottomLeftViewport->GetCanvas()->Refresh();
		m_bottomRightViewport->GetCanvas()->Refresh();

		m_lastUpdateTime = updateTime;
	}
}

void reViewportDisplay::OnDisplayShouldUpdate(rEvent& event){
	UpdateAllViewports();
}

void reViewportDisplay::OnCommandProcessed(rEvent& event){
	UpdateAllViewports();
}

void reViewportDisplay::MaximizeViewport(int id){
	if (m_isMaximized) return;

	SaveViewportLayout();

	if (id == m_topLeftViewport->GetCanvas()->GetId()){
		m_leftSplitter->Unsplit(m_bottomLeftViewport);
		m_mainSplitter->Unsplit(m_rightSplitter);
	}
	else if (id == m_bottomLeftViewport->GetCanvas()->GetId()){
		m_leftSplitter->Unsplit(m_topLeftViewport);
		m_mainSplitter->Unsplit(m_rightSplitter);
	}
	else if (id == m_topRightViewport->GetCanvas()->GetId()){
		m_rightSplitter->Unsplit(m_bottomRightViewport);
		m_mainSplitter->Unsplit(m_leftSplitter);
	}
	else if (id == m_bottomRightViewport->GetCanvas()->GetId()){
		m_rightSplitter->Unsplit(m_topRightViewport);
		m_mainSplitter->Unsplit(m_leftSplitter);
	}

	m_isMaximized = true;
}

void reViewportDisplay::RestoreViewports(){
	if (!m_isMaximized) return;

	if (m_splitterInfo[0].first)
		m_leftSplitter->SplitHorizontally(m_topLeftViewport, m_bottomLeftViewport, m_splitterInfo[0].second);

	if (m_splitterInfo[1].first)
		m_rightSplitter->SplitHorizontally(m_topRightViewport, m_bottomRightViewport, m_splitterInfo[1].second);

	if (m_splitterInfo[2].first)
		m_mainSplitter->SplitVertically(m_leftSplitter, m_rightSplitter, m_splitterInfo[2].second);

	m_isMaximized = false;
}

void reViewportDisplay::SaveViewportLayout(){
	m_splitterInfo[0].first = m_leftSplitter->IsSplit();
	m_splitterInfo[0].second = m_leftSplitter->GetSashPosition();

	m_splitterInfo[1].first = m_rightSplitter->IsSplit();
	m_splitterInfo[1].second = m_rightSplitter->GetSashPosition();

	m_splitterInfo[2].first = m_mainSplitter->IsSplit();
	m_splitterInfo[2].second = m_mainSplitter->GetSashPosition();
}

void reViewportDisplay::CharHook(wxKeyEvent& event) {
	if (m_hoverCanvas) {
		m_toolManager->OnKeyPress(event, m_hoverCanvas);
	}
}

void reViewportDisplay::HoverCanvas(rwxGLCanvas* canvas) {
	m_hoverCanvas = canvas;
}