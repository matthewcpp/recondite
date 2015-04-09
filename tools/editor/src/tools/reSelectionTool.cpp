#include "reSelectionTool.hpp"

reSelectionTool::reSelectionTool(reComponent* component, wxFrame* owner)
	:reToolBase(component, owner)
{

}

wxString reSelectionTool::GetToolName() const{
	return "Selection Tool";
}

bool reSelectionTool::OnMouseUp(wxMouseEvent& event, rwxGLCanvas* canvas){
	reToolBase::OnMouseUp(event, canvas);

	if (IsClick()){
		rViewport* viewport = canvas->GetViewport();
		rScene* scene = m_component->GetScene();

		rPoint pt(m_currentPoint.x, m_currentPoint.y);
		rRay3 selectionRay;
		viewport->GetSelectionRay(pt, selectionRay);

		rActor3* actor = scene->RayPick(selectionRay);

		if (actor){
			m_component->GetSelection()->AddSelection(actor->Id().c_str());
			return true;
		}
		else{
			m_component->GetSelection()->ClearSelection();
			return false;
		}
	}

	return false;
}