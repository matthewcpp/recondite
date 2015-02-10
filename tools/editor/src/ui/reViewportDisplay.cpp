#include "reViewportDisplay.hpp"

reViewportDisplay::reViewportDisplay(rwxComponent* component, reToolManager* toolManager, wxWindow* parent, wxWindowID id)
	:wxPanel(parent, id)
{
	m_component = component;
	m_toolManager = toolManager;

	CreateViewportDisplay();
}

void reViewportDisplay::CreateViewportDisplay(){
	m_mainSplitter = new wxSplitterWindow(this, wxID_ANY);
	m_mainSplitter->SetSashGravity(0.5);

	m_leftSplitter = new wxSplitterWindow(m_mainSplitter, wxID_ANY);
	m_leftSplitter->SetSashGravity(0.5);

	m_topLeftViewport = new reViewport(m_component, m_toolManager, "Viewport 1", m_leftSplitter);
	m_bottomLeftViewport = new reViewport(m_component, m_toolManager, "Viewport 2", m_leftSplitter);
	m_leftSplitter->SplitHorizontally(m_topLeftViewport, m_bottomLeftViewport);

	m_rightSplitter = new wxSplitterWindow(m_mainSplitter, wxID_ANY);
	m_rightSplitter->SetSashGravity(0.5);

	m_topRightViewport = new reViewport(m_component, m_toolManager, "Viewport 3", m_rightSplitter);
	m_bottomRightViewport = new reViewport(m_component, m_toolManager, "Viewport 4", m_rightSplitter);
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