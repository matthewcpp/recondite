#include "reViewportDisplay.hpp"

reViewportDisplay::reViewportDisplay(rwxComponent* component, wxWindow* parent, wxWindowID id)
	:wxPanel(parent, id)
{
	m_component = component;

	CreateViewportDisplay();
}

void reViewportDisplay::CreateViewportDisplay(){
	m_mainSplitter = new wxSplitterWindow(this, wxID_ANY);
	m_mainSplitter->SetSashGravity(0.5);

	m_leftSplitter = new wxSplitterWindow(m_mainSplitter, wxID_ANY);
	m_leftSplitter->SetSashGravity(0.5);

	m_topLeftViewport = new reViewport(m_component, m_leftSplitter);
	m_bottomLeftViewport = new reViewport(m_component, m_leftSplitter);
	m_leftSplitter->SplitHorizontally(m_topLeftViewport, m_bottomLeftViewport);

	m_rightSplitter = new wxSplitterWindow(m_mainSplitter, wxID_ANY);
	m_rightSplitter->SetSashGravity(0.5);

	m_topRightViewport = new reViewport(m_component, m_rightSplitter);
	m_bottomRightViewport = new reViewport(m_component, m_rightSplitter);
	m_rightSplitter->SplitHorizontally(m_topRightViewport, m_bottomRightViewport);

	m_mainSplitter->SplitVertically(m_leftSplitter, m_rightSplitter);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(m_mainSplitter, 1, wxEXPAND | wxALL, 2);
	SetSizer(mainSizer);
}