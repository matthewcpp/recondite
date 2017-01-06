#include "rePaletteDropTarget.hpp"

#include "rPickResult.hpp"

rePaletteDropTarget::rePaletteDropTarget(reComponent* component, rwxGLCanvas* canvas){
	m_component = component;
	m_canvas = canvas;
}

bool rePaletteDropTarget::OnDropText(wxCoord x, wxCoord y, const wxString &data){
	rViewport* viewport = m_canvas->GetViewport();
	rScene* scene = m_component->GetScene();

	rPoint pt(x, y);
	rRay3 selectionRay;
	viewport->GetSelectionRay(pt, selectionRay);

	rPickResult result;
	scene->RayPick(selectionRay, result);
	if (result.hit) {
		reInsertActorCommand* insertActorCommand = new reInsertActorCommand(data, result.point, m_component);
		m_component->SubmitCommand(insertActorCommand);
		return true;
	}

	return false;
}