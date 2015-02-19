#include "reToolBase.hpp"

reToolBase::reToolBase(rwxComponent* component, wxFrame* owner)
	:reTool(component, owner)
{}

bool reToolBase::IsClick(){
	return m_currentPoint == m_firstPoint;
}

bool reToolBase::OnMouseDown(wxMouseEvent& event, rwxGLCanvas* canvas){
	m_firstPoint = event.GetPosition();
	m_currentPoint = m_firstPoint;
	m_previousPoint = m_firstPoint;

	return false;
}

bool reToolBase::OnMouseUp(wxMouseEvent& event, rwxGLCanvas* canvas){
	UpdatePoints(event);
	return false;
}

bool reToolBase::OnMouseMotion(wxMouseEvent& event, rwxGLCanvas* canvas){
	UpdatePoints(event);
	return false;
}

void reToolBase::UpdatePoints(wxMouseEvent& event){
	m_previousPoint = m_currentPoint;
	m_currentPoint = event.GetPosition();
}