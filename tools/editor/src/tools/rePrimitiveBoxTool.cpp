#include "rePrimitiveBoxTool.hpp"

rePrimitiveBoxTool::rePrimitiveBoxTool(rwxComponent* component, wxFrame* owner)
	:reTool(component, owner)
{
}

bool rePrimitiveBoxTool::OnMouseDown(wxMouseEvent& event, rwxGLCanvas* canvas){
	return false;
}

bool rePrimitiveBoxTool::OnMouseUp(wxMouseEvent& event, rwxGLCanvas* canvas){
	rViewport* viewport = canvas->GetViewport();
	rRay3 selectionRay;
	rPoint pt(event.GetX(), event.GetY());
	viewport->GetSelectionRay(pt, selectionRay);

	rVector3 position = rVector3::ZeroVector;
	rPlane groundPlane(rVector3::ForwardVector, 0.0f);

	if (rIntersection::RayIntersectsPlane(selectionRay, groundPlane, &position)){
		rEngine* engine = m_component->GetEngine();
		rString id = engine->scene->GetDefaultActorId("box");
		rPrimitiveBox* box = new rPrimitiveBox(id, engine);
		box->SetPosition(position);
		engine->scene->AddActor(box);

		return true;
	}

	return false;
}

bool rePrimitiveBoxTool::OnMouseMotion(wxMouseEvent& event, rwxGLCanvas* canvas){
	return false;
}