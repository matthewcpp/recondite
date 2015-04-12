#include "reToolBase.hpp"

reToolBase::reToolBase(reComponent* component, wxFrame* owner)
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

rActor3* reToolBase::PickActor(wxMouseEvent& event, rwxGLCanvas* canvas){
	rViewport* viewport = canvas->GetViewport();
	rScene* scene = m_component->GetScene();

	rPoint pt(m_currentPoint.x, m_currentPoint.y);
	rRay3 selectionRay;
	viewport->GetSelectionRay(pt, selectionRay);

	return scene->RayPick(selectionRay);
}

bool reToolBase::DoClearSelection(){
	size_t selectionCount = m_component->SelectionManager()->GetSelection().size();
	m_component->SelectionManager()->ClearSelection();
	return selectionCount > 0;
}

bool reToolBase::DoActorSelection(rActor3* actor, wxMouseEvent& event){
	if (event.ShiftDown()){
		m_component->SelectionManager()->AddSelection(actor->Id().c_str());
	}
	else{
		m_component->SelectionManager()->Select(actor->Id().c_str());
	}
	
	return true;
}