#include "rePaletteDropTarget.hpp"

rePaletteDropTarget::rePaletteDropTarget(reComponent* component, rwxGLCanvas* canvas){
	m_component = component;
	m_canvas = canvas;
}

bool rePaletteDropTarget::OnDropText(wxCoord x, wxCoord y, const wxString &data){
	rEngine* engine = m_component->GetEngine();
	rString actorId = engine->scene->GetDefaultActorId("actor");
	rActor3* actor = engine->actors->GetActorClass(data.c_str().AsChar(), engine, actorId);
	engine->scene->AddActor(actor);

	rCamera* camera = m_canvas->GetCamera();
	rVector3 target = camera->Target();
	rVector3 viewDir = camera->Position() - target;
	viewDir.Normalize();

	rPlane targetPlane(target, viewDir);
	rRay3 selectionRay;
	rPoint p(x, y);
	m_canvas->GetViewport()->GetSelectionRay(p, selectionRay);

	rVector3 planePos;
	rIntersection::RayIntersectsPlane(selectionRay, targetPlane, &planePos);

	actor->SetPosition(planePos);
	m_component->GetSelection()->Select(actor->Id().c_str());
	return true;
}