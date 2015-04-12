#include "tools/reTranslateTool.hpp"

reTranslateTool::reTranslateTool(reComponent* component, wxFrame* owner)
	: reToolBase(component, owner)
{
	m_gizmo.reset(new reTranslateGizmo(component));
}

bool reTranslateTool::OnMouseDown(wxMouseEvent& event, rwxGLCanvas* canvas){
	rViewport* viewport = canvas->GetViewport();
	rScene* scene = m_component->GetScene();

	rPoint pt(m_currentPoint.x, m_currentPoint.y);
	rRay3 selectionRay;
	viewport->GetSelectionRay(pt, selectionRay);

	rActor3* actor = scene->RayPick(selectionRay);

	if (actor){
		if (m_gizmo->ContainsActor(actor)){
			//start dragging
		}
		else{
			m_component->GetSelection()->Select(actor->Id().c_str());
			rVector3 center = actor->BoundingVolume()->FitBox().Center();
			m_gizmo->SetVisibility(true);
			m_gizmo->SetPosition(center);
		}

		return true;
	}
	else{
		m_gizmo->SetVisibility(false);
		size_t selectionCount = m_component->GetSelection()->GetSelection().size();
		m_component->GetSelection()->ClearSelection();
		return selectionCount > 0;
	}
}

void reTranslateTool::OnActivate(){
	m_gizmo->Update();
}

wxString reTranslateTool::GetToolName() const{
	return "Translate Tool";
}