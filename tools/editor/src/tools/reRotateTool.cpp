#include "tools/reRotateTool.hpp"

reRotateTool::reRotateTool(reComponent* component, wxFrame* owner)
	:reToolBase(component, owner)
{
	m_command = nullptr;
	m_selectedAxis = reGizmoAxis::NONE;
	m_rotationSpeed = 1.0f;
}

reRotateTool::~reRotateTool() {
	if (m_command) delete m_command;
}

bool reRotateTool::OnMouseDown(wxMouseEvent& event, rwxGLCanvas* canvas) {
	reToolBase::OnMouseDown(event, canvas);

	m_component->GetEngine()->viewports->SetActiveViewport(canvas->GetViewport());
	m_gizmo->Update();

	rRay3 selectionRay = GetSelectionRay(event, canvas);
	m_selectedAxis = m_gizmo->PickAxis(selectionRay);

	if (m_selectedAxis != reGizmoAxis::NONE) {
		m_gizmo->HighlightAxis(m_selectedAxis);

		wxPoint eventPoint = event.GetPosition();
		m_previousPoint.Set(eventPoint.x, eventPoint.y);

		m_command = new reRotateCommand(m_component->SelectionManager()->GetSelection(), m_component);
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

bool reRotateTool::OnMouseMotion(wxMouseEvent& event, rwxGLCanvas* canvas) {
	reToolBase::OnMouseMotion(event, canvas);

	m_component->GetEngine()->viewports->SetActiveViewport(canvas->GetViewport());

	if (m_selectedAxis == reGizmoAxis::NONE) {
		return false;
	}
	else {
		wxPoint eventPoint = event.GetPosition();
		rPoint currentPoint(eventPoint.x, eventPoint.y);

		rPoint delta = currentPoint - m_previousPoint;
		rVector3 rotationDelta = rVector3::ZeroVector;
		float rotationAmount = m_rotationSpeed * currentPoint.Distance(m_previousPoint);

		switch (m_selectedAxis) {
			case reGizmoAxis::Y: {
				rotationDelta.y += rotationAmount;
				if (delta.x < 0) rotationDelta *= -1;
				break;
			}

			case reGizmoAxis::X: {
				rotationDelta.x += rotationAmount;
				if (delta.y > 0) rotationDelta *= -1;
				break;
			}

			case reGizmoAxis::Z: {
				rotationDelta.z += rotationAmount;
				if (delta.y > 0) rotationDelta *= -1;
				break;
			}
		}

		m_command->Update(rotationDelta);

		rEvent event;
		m_component->Trigger(reExternalPropertyChange, event);

		m_previousPoint = currentPoint;

		return true;
	}
}

bool reRotateTool::OnMouseUp(wxMouseEvent& event, rwxGLCanvas* canvas) {
	reToolBase::OnMouseUp(event, canvas);

	if (m_command) {
		m_component->SubmitCommand(m_command);

		m_gizmo->UnhighlightAxis(m_selectedAxis);
		m_selectedAxis = reGizmoAxis::NONE;
		m_command = nullptr;

		return true;
	}

	return false;
}

void reRotateTool::SetDragPlaneFromSelectedAxis() {
	switch (m_selectedAxis) {
	case reGizmoAxis::Y:
		m_dragPlane.SetFromPointAndNormal(m_gizmo->GetPosition(), rVector3::UpVector);
		break;
	}
}

bool reRotateTool::GetWorldSpaceDragPosition(rwxGLCanvas* canvas, rVector3& result) {
	recondite::Camera* camera = canvas->GetCamera();
	rViewport* viewport = canvas->GetViewport();

	rPoint pt(m_currentPoint.x, m_currentPoint.y);
	rRay3 selectionRay;
	viewport->GetSelectionRay(pt, selectionRay);

	return rIntersection::RayIntersectsPlane(selectionRay, m_dragPlane, &result);
}

wxString reRotateTool::GetToolName() const {
	return "Rotate Tool";
}

void reRotateTool::Init() {
	m_gizmo.reset(new reRotateGizmo(m_component));
}

void reRotateTool::OnActivate() {
	m_gizmo->Update();
}

void reRotateTool::OnDeactivate() {
	m_gizmo->Update();
	m_gizmo->SetVisibility(false);
}