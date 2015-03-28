#include "tools/rePrimitiveConeTool.hpp"

rePrimitiveConeTool::rePrimitiveConeTool(reComponent* component, wxFrame* owner)
	:reToolBase(component, owner)
{
}

bool rePrimitiveConeTool::OnMouseUp(wxMouseEvent& event, rwxGLCanvas* canvas){
	reToolBase::OnMouseUp(event, canvas);

	if (IsClick()){
		rViewport* viewport = canvas->GetViewport();
		rRay3 selectionRay;
		rPoint pt(event.GetX(), event.GetY());
		viewport->GetSelectionRay(pt, selectionRay);

		rVector3 position = rVector3::ZeroVector;
		rPlane groundPlane(rVector3::UpVector, 0.0f);

		if (rIntersection::RayIntersectsPlane(selectionRay, groundPlane, &position)){
			rEngine* engine = m_component->GetEngine();
			rString id = engine->scene->GetDefaultActorId("cone");
			rPrimitiveCone* cone = new rPrimitiveCone(id, engine);
			cone->SetPosition(position);
			engine->scene->AddActor(cone);

			return true;
		}
	}

	return false;
}