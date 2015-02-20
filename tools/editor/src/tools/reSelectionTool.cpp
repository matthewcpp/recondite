#include "reSelectionTool.hpp"

reSelectionTool::reSelectionTool(rwxComponent* component, wxFrame* owner)
	:reToolBase(component, owner)
{

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
			return true;
		}
		else{
			return false;
		}
	}
}