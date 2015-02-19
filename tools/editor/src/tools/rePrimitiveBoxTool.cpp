#include "rePrimitiveBoxTool.hpp"

rePrimitiveBoxTool::rePrimitiveBoxTool(rwxComponent* component, wxFrame* owner)
	:reToolBase(component, owner)
{
}

bool rePrimitiveBoxTool::OnMouseUp(wxMouseEvent& event, rwxGLCanvas* canvas){
	reToolBase::OnMouseUp(event, canvas);

	if (IsClick()){
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
	}

	return false;
}