#include "tools/reRotateGizmo.hpp"

#include "asset/rModelData.hpp"
#include "primitive/rPrimitiveGeometry.hpp"
#include "reGizmo.hpp"

#define GIZMO_RADIUS 15.0f

reRotateGizmo::reRotateGizmo(reComponent* component) 
:reTransformGizmoBase(component)
{}

void reRotateGizmo::Update() {
	if (!m_xHandle)
		CreateGeometry();

	const wxArrayString& selection = m_component->SelectionManager()->GetSelection();

	if (selection.size() == 0) {
		SetVisibility(false);
	}
	else {
		rScene* scene = m_component->GetScene();
		rAlignedBox3 selectionBounding, actorBounding;

		for (size_t i = 0; i < selection.size(); i++) {
			rActor3* actor = scene->GetActor(selection[i].c_str().AsChar());
			actorBounding = actor->WorldBounding();
			selectionBounding.AddBox(actorBounding);
		}

		SetPosition(selectionBounding.Center());
		SetVisibility(true);
	}
}

void reRotateGizmo::CreateGeometry() {
	rEngine* engine = m_component->GetEngine();

	recondite::ModelData modelData;
	rPrimitiveGeometry::rPrimitiveCircleParams circle;
	circle.radius = GIZMO_RADIUS;
	rPrimitiveGeometry::CreateCircle(circle, modelData);

	while (modelData.GetTriangleMeshCount() > 0) {
		modelData.DeleteTriangleMesh(modelData.GetTriangleMeshCount() - 1);
	}

	modelData.CalculateBoundings();

	recondite::Model* handleModel = engine->content->Models()->LoadFromData(modelData, "__rotate_gizmo_handle__");

	m_xHandle = new reGizmoHandle(handleModel, "__rotate_x_handle__", engine);
	m_xHandle->SetRenderModeOverride(rRenderMode::Wireframe);
	m_xHandle->SetRotation(rVector3(90.0, 90.0f, 0.0f));
	m_xHandle->GetModelInstance()->GetLineMeshInstanceMaterial(0)->SetDiffuseColor(rColor::Red);
	m_xHandle->SetPickable(false);

	m_yHandle = new reGizmoHandle(handleModel, "__rotate_y_handle__", engine);
	m_yHandle->SetRenderModeOverride(rRenderMode::Wireframe);
	m_yHandle->GetModelInstance()->GetLineMeshInstanceMaterial(0)->SetDiffuseColor(rColor::Green);
	m_yHandle->SetPickable(false);

	m_zHandle = new reGizmoHandle(handleModel, "__rotate_z_handle__", engine);
	m_zHandle->SetRenderModeOverride(rRenderMode::Wireframe);
	m_zHandle->SetRotation(rVector3(90.0, 0.0f, 0.0f));
	m_zHandle->GetModelInstance()->GetLineMeshInstanceMaterial(0)->SetDiffuseColor(rColor::Blue);
	m_zHandle->SetPickable(false);

	engine->scene->AddActor(m_xHandle);
	engine->scene->AddActor(m_yHandle);
	engine->scene->AddActor(m_zHandle);
}

reGizmoAxis reRotateGizmo::PickAxis(const rRay3& ray) {
	reGizmoAxis bestAxis = reGizmoAxis::NONE;
	float tolerance = 2.0f;
	
	float bestDistance = FLT_MAX;

	rVector3 position;
	rPlane handle(m_currentPosition, rVector3::UpVector);
	if (rIntersection::RayIntersectsPlane(ray, handle, &position)) {
		float planeDistance = m_currentPosition.Distance(position);
		float rayDistance = ray.origin.Distance(position);
		
		m_yHandle->UpdateScale();
		float visualRadius = GIZMO_RADIUS * m_yHandle->GetScaleFactor();
		float visualTolerance = tolerance * m_yHandle->GetScaleFactor();

		if ((planeDistance > visualRadius - visualTolerance) && (planeDistance < visualRadius + visualTolerance) && (rayDistance < bestDistance) ) {
			bestDistance = rayDistance;
			bestAxis = reGizmoAxis::Y;
		}
	}

	handle.SetFromPointAndNormal(m_currentPosition, rVector3::RightVector);
	if (rIntersection::RayIntersectsPlane(ray, handle, &position)) {
		float planeDistance = m_currentPosition.Distance(position);
		float rayDistance = ray.origin.Distance(position);

		m_xHandle->UpdateScale();
		float visualRadius = GIZMO_RADIUS * m_xHandle->GetScaleFactor();
		float visualTolerance = tolerance * m_xHandle->GetScaleFactor();

		if ((planeDistance > visualRadius - visualTolerance) && (planeDistance < visualRadius + visualTolerance) && (rayDistance < bestDistance)) {
			bestDistance = rayDistance;
			bestAxis = reGizmoAxis::X;
		}
	}

	handle.SetFromPointAndNormal(m_currentPosition, rVector3::ForwardVector);
	if (rIntersection::RayIntersectsPlane(ray, handle, &position)) {
		float planeDistance = m_currentPosition.Distance(position);
		float rayDistance = ray.origin.Distance(position);

		m_zHandle->UpdateScale();
		float visualRadius = GIZMO_RADIUS * m_zHandle->GetScaleFactor();
		float visualTolerance = tolerance * m_zHandle->GetScaleFactor();

		if ((planeDistance > visualRadius - visualTolerance) && (planeDistance < visualRadius + visualTolerance) && (rayDistance < bestDistance)) {
			bestDistance = rayDistance;
			bestAxis = reGizmoAxis::Z;
		}
	}

	return bestAxis;
}