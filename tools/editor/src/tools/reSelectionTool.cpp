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
		rActor3* actor = PickActor(event, canvas);

		if (actor){
			return DoActorSelection(actor, event);
		}
		else{
			return DoClearSelection();
		}
	}

	return false;
}