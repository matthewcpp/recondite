#include "tools/rePrimitiveGridTool.hpp"

rePrimitiveGridTool::rePrimitiveGridTool(reComponent* component, wxFrame* owner)
	:reToolBase(component, owner)
{

}

bool rePrimitiveGridTool::OnMouseUp(wxMouseEvent& event, rwxGLCanvas* canvas){
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
			rString id = engine->scene->GetDefaultActorId("grid");

			rPrimitiveGrid* grid = new rPrimitiveGrid(id, engine);
			grid->SetPosition(position);
			engine->scene->AddActor(grid);
			return true;
		}
	}

	return false;
}