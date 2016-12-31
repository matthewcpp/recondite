#include "tools/reTranslateTool.hpp"



reTranslateTool::reTranslateTool(reComponent* component, wxFrame* owner)
	: reToolBase(component, owner)
{
	m_command = nullptr;
	m_selectedAxis = reGizmo::Axis::NONE;
}

reTranslateTool::~reTranslateTool(){
	if (m_command) delete m_command;
}

bool reTranslateTool::OnMouseDown(wxMouseEvent& event, rwxGLCanvas* canvas){
	reToolBase::OnMouseDown(event, canvas);

	m_component->SetActiveViewport(canvas->GetViewport());

	rRay3 selectionRay = GetSelectionRay(event, canvas);
	m_selectedAxis = m_gizmo->PickAxis(selectionRay);

	if (m_selectedAxis != reGizmo::Axis::NONE) {
		m_gizmo->HighlightAxis(m_selectedAxis);
		m_gizmo->Update();
		SetDragPlaneFromSelectedAxis();
		GetWorldSpaceDragPosition(canvas, m_previousWorldPosition);
		m_command = new reTranslateCommand(m_component->SelectionManager()->GetSelection(), m_component);

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

bool reTranslateTool::OnMouseUp(wxMouseEvent& event, rwxGLCanvas* canvas){
	reToolBase::OnMouseUp(event, canvas);

	if (m_command){
		m_component->SubmitCommand(m_command);

		m_gizmo->UnhighlightAxis(m_selectedAxis);
		m_selectedAxis = reGizmo::Axis::NONE;
		m_command = nullptr;
		
		return true;
	}

	return false;
}

bool reTranslateTool::OnMouseMotion(wxMouseEvent& event, rwxGLCanvas* canvas){
	reToolBase::OnMouseMotion(event, canvas);

	if (m_selectedAxis == reGizmo::Axis::NONE){
		return false;
	}
	else{
		rVector3 currentWorldSpacePosition;
		GetWorldSpaceDragPosition(canvas, currentWorldSpacePosition);
		rVector3 delta = currentWorldSpacePosition - m_previousWorldPosition;

		switch (m_selectedAxis){
		case reGizmo::Axis::X:
			delta.Set(delta.x, 0.0f, 0.0f);
			break;

		case reGizmo::Axis::Y:
			delta.Set(0.0f, delta.y, 0.0f);
			break;

		case reGizmo::Axis::Z:
			delta.Set(0.0f, 0.0f, delta.z);
			break;
		}

		m_command->Update(delta);
		m_gizmo->Update();
		
		rEvent event;
		m_component->Trigger(reExternalPropertyChange, event);

		m_previousWorldPosition = currentWorldSpacePosition;

		return true;
	}
}

void reTranslateTool::OnActivate(){
	m_gizmo->Update();
}

void reTranslateTool::OnDeactivate() {
	m_gizmo->SetVisibility(false);
}

void reTranslateTool::OnUpdate(){
	m_gizmo->Update();
}

wxString reTranslateTool::GetToolName() const{
	return "Translate Tool";
}

void reTranslateTool::SetDragPlaneFromSelectedAxis(){
	switch (m_selectedAxis){
	case reGizmo::Axis::X:
	case reGizmo::Axis::Y:
		m_dragPlane.SetFromPointAndNormal(m_gizmo->GetPosition(), rVector3::BackwardVector);
		break;

	case reGizmo::Axis::Z:
		m_dragPlane.SetFromPointAndNormal(m_gizmo->GetPosition(), rVector3::RightVector);
		break;
	}
}

bool reTranslateTool::GetWorldSpaceDragPosition(rwxGLCanvas* canvas, rVector3& result){
	recondite::Camera* camera = canvas->GetCamera();
	rViewport* viewport = canvas->GetViewport();

	rPoint pt(m_currentPoint.x, m_currentPoint.y);
	rRay3 selectionRay;
	viewport->GetSelectionRay(pt, selectionRay);
	
	return rIntersection::RayIntersectsPlane(selectionRay, m_dragPlane, &result);
}

void reTranslateTool::Init() {
	m_gizmo.reset(new Gizmo(m_component));
}

reTranslateTool::Gizmo::Gizmo(reComponent* component)
	:reGizmo(component)
{

}

void reTranslateTool::Gizmo::CreateGizmoHandle(recondite::ModelData& modelData) {
	rPrimitiveGeometry::rPrimitiveCylinderParams cylinderParams(0.3f, 7, 20);
	rPrimitiveGeometry::CreateCylinder(cylinderParams, modelData);

	recondite::GeometryData* geometryData = modelData.GetGeometryData();
	size_t vertexOffset = geometryData->VertexCount();

	rPrimitiveGeometry::rPrimitiveConeParams coneParams(1.0, 2.5, 20);
	rPrimitiveGeometry::CreateCone(coneParams, modelData);

	rMatrix4 transform;
	transform.SetTranslate(0.0f, cylinderParams.height, 0.0f);

	geometryData->TransformVertices(vertexOffset, geometryData->VertexCount() - vertexOffset, transform);

}