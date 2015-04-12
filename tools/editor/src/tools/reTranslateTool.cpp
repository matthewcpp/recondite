#include "tools/reTranslateTool.hpp"

reTranslateTool::reTranslateTool(reComponent* component, wxFrame* owner)
	: reToolBase(component, owner)
{
	m_gizmo.reset(new reTranslateGizmo(component));
}

bool reTranslateTool::OnMouseDown(wxMouseEvent& event, rwxGLCanvas* canvas){
	reToolBase::OnMouseDown(event, canvas);

	rActor3* actor = PickActor(event, canvas);

	if (actor){
		if (m_gizmo->ContainsActor(actor)){
			//start dragging
		}
		else{
			bool result = DoActorSelection(actor, event);
			m_gizmo->Update();
		}

		return true;
	}
	else{
		m_gizmo->SetVisibility(false);
		return DoClearSelection();
	}
}

void reTranslateTool::OnActivate(){
	m_gizmo->Update();
}

wxString reTranslateTool::GetToolName() const{
	return "Translate Tool";
}