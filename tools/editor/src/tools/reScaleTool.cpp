#include "tools/reScaleTool.hpp"

reScaleTool::reScaleTool(reComponent* component, wxFrame* owner)
	: reToolBase(component, owner)
{
	m_command = nullptr;
	m_selectedAxis = reGizmoAxis::NONE;
	m_previousWorldPosition = rVector3::ZeroVector;
}

reScaleTool::~reScaleTool() {
	if (m_command) delete m_command;
}

bool reScaleTool::OnMouseDown(wxMouseEvent& event, rwxGLCanvas* canvas) {
	reToolBase::OnMouseDown(event, canvas);

	m_component->SetActiveViewport(canvas->GetViewport());
	m_gizmo->Update();

	rRay3 selectionRay = GetSelectionRay(event, canvas);
	m_selectedAxis = m_gizmo->PickAxis(selectionRay);

	if (m_selectedAxis != reGizmoAxis::NONE) {
		m_gizmo->HighlightAxis(m_selectedAxis);
		
		SetDragPlane(selectionRay);
		GetWorldSpaceDragPosition(canvas, m_previousWorldPosition);

		m_command = new reScaleCommand(m_component->SelectionManager()->GetSelection(), m_component);

		return true;
	}
	else {
		rActor3* actor = PickActor(event, canvas);

		if (actor) {
			bool result = DoActorSelection(actor, event);
			m_gizmo->Update();

			return true;
		}
		else {
			m_gizmo->SetVisibility(false);
			return DoClearSelection();
		}
	}
}

bool reScaleTool::OnMouseMotion(wxMouseEvent& event, rwxGLCanvas* canvas) {
	reToolBase::OnMouseMotion(event, canvas);

	m_component->SetActiveViewport(canvas->GetViewport());

	if (m_selectedAxis == reGizmoAxis::NONE) {
		return false;
	}
	else {
		rVector3 currentWorldPosition = rVector3::ZeroVector;
		rVector3 scaleDelta = rVector3::ZeroVector;

		GetWorldSpaceDragPosition(canvas, currentWorldPosition);
		

		if (m_selectedAxis == reGizmoAxis::ALL) {
			//scale value is determined by mouse movement in screen space
			float scaleAmount = currentWorldPosition.Distance(m_previousWorldPosition) * 0.25;

			wxPoint delta = m_currentPoint - m_previousPoint;
			if (delta.y > 0 || delta.x < 0) scaleAmount *= -1;
			scaleDelta.Set(scaleAmount, scaleAmount, scaleAmount);
		}
		else {
			rVector3 delta = currentWorldPosition - m_previousWorldPosition;

			switch (m_selectedAxis) {
				case reGizmoAxis::X: {
					reScaleGizmoHandle* handle = (reScaleGizmoHandle*)m_gizmo->GetHandle(reGizmoAxis::X);
					rVector3 position = handle->Position();
					rVector3 newPosition(position.x + delta.x, position.y, position.z);
					float deltaDistance = position.Distance(newPosition);

					if (delta.x < 0) deltaDistance *= -1;

					handle->SetStemLength(handle->GetStemLength() + deltaDistance);
					scaleDelta.x = deltaDistance * 0.25;

					break;
				}

				case reGizmoAxis::Y: {
					reScaleGizmoHandle* handle = (reScaleGizmoHandle*)m_gizmo->GetHandle(reGizmoAxis::Y);
					rVector3 position = handle->Position();
					rVector3 newPosition(position.x, position.y + delta.y, position.z);
					float deltaDistance = position.Distance(newPosition);

					if (delta.y < 0) deltaDistance *= -1;

					handle->SetStemLength(handle->GetStemLength() + deltaDistance);
					scaleDelta.y = deltaDistance * 0.25;

					break;
				}

				case reGizmoAxis::Z: {
					reScaleGizmoHandle* handle = (reScaleGizmoHandle*)m_gizmo->GetHandle(reGizmoAxis::Z);
					rVector3 position = handle->Position();
					rVector3 newPosition(position.x, position.y, position.z+ delta.z);
					float deltaDistance = position.Distance(newPosition);

					if (delta.z < 0) deltaDistance *= -1;

					handle->SetStemLength(handle->GetStemLength() + deltaDistance);
					scaleDelta.z = deltaDistance * 0.25;

					break;
				}
			}
		}

		m_command->Update(scaleDelta);

		rEvent event;
		m_component->Trigger(reExternalPropertyChange, event);

		m_previousWorldPosition = currentWorldPosition;
		
		return true;
	}
}

bool reScaleTool::OnMouseUp(wxMouseEvent& event, rwxGLCanvas* canvas) {
	reToolBase::OnMouseUp(event, canvas);

	if (m_command) {
		m_component->SubmitCommand(m_command);

		m_gizmo->UnhighlightAxis(m_selectedAxis);
		m_gizmo->ResetStems();
		m_selectedAxis = reGizmoAxis::NONE;
		m_command = nullptr;

		return true;
	}

	return false;
}

void reScaleTool::SetDragPlane(const rRay3& selectionRay) {
	rVector3 gizmoPosition = m_gizmo->GetPosition();

	if (m_selectedAxis == reGizmoAxis::ALL){
		recondite::Camera* camera = m_component->GetEngine()->component->GetActiveViewport()->Camera();
		rVector3 direction = camera->GetPosition() - gizmoPosition;
		direction.Normalize();
		m_dragPlane.SetFromPointAndNormal(gizmoPosition, direction);
	}
	else {
		m_dragPlane = reToolBase::GetDragPlaneFromRay(selectionRay);
	}

}

bool reScaleTool::GetWorldSpaceDragPosition(rwxGLCanvas* canvas, rVector3& result) {
	recondite::Camera* camera = canvas->GetCamera();
	rViewport* viewport = canvas->GetViewport();

	rPoint pt(m_currentPoint.x, m_currentPoint.y);
	rRay3 selectionRay;
	viewport->GetSelectionRay(pt, selectionRay);

	return rIntersection::RayIntersectsPlane(selectionRay, m_dragPlane, &result);
}

wxString reScaleTool::GetToolName() const {
	return "Scale";
}

void reScaleTool::OnActivate() {
	m_gizmo->Update();
}

void reScaleTool::OnDeactivate() {
	m_gizmo->Update();
	m_gizmo->SetVisibility(false);
}

void reScaleTool::OnUpdate() {
	m_gizmo->Update();
}

void reScaleTool::Init() {
	m_gizmo.reset(new reScaleGizmo(m_component));
}