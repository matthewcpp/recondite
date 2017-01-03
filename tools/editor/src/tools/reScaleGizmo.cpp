#include "tools/reScaleGizmo.hpp"

#include "asset/rModelData.hpp"
#include "primitive/rPrimitiveGeometry.hpp"
#include "reGizmo.hpp"

reScaleGizmo::reScaleGizmo(reComponent* component) {
	m_component = component;

	m_uniformScaleHandle = nullptr;
}

void reScaleGizmo::Update() {
	if (!m_uniformScaleHandle)
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
void reScaleGizmo::SetVisibility(bool visibility) {
	m_uniformScaleHandle->RenderingOptions()->SetVisibility(visibility);
}

void reScaleGizmo::CreateGeometry() {
	rEngine* engine = m_component->GetEngine();

	recondite::ModelData modelData;
	rPrimitiveGeometry::rPrimitiveBoxParams box;
	rPrimitiveGeometry::CreateBox(box, modelData);

	rMatrix4 translateMatrix;
	translateMatrix.SetTranslate(0, -0.5, 0);

	recondite::GeometryData* geometryData = modelData.GetGeometryData();
	geometryData->TransformVertices(0, geometryData->VertexCount(), translateMatrix);

	modelData.CalculateBoundings();

	recondite::Model* handleModel = engine->content->Models()->LoadFromData(modelData, "__rotate_gizmo_handle__");

	m_uniformScaleHandle = new reGizmoHandle(handleModel, "__rotate_uniform_handle__", engine);
	m_uniformScaleHandle->GetModelInstance()->GetTriangleMeshInstanceMaterial(0)->SetDiffuseColor(rColor(130,130,130,255));
	m_uniformScaleHandle->SetPickable(false);

	engine->scene->AddActor(m_uniformScaleHandle);
}

void reScaleGizmo::SetPosition(const rVector3& position) {
	m_uniformScaleHandle->SetPosition(position);
}

reGizmoAxis reScaleGizmo::PickAxis(const rRay3& ray) {
	rPickResult xResult, yResult, zResult, uniformResult;
	rActor3* best = nullptr;
	float bestDistance = FLT_MAX;

	m_uniformScaleHandle->RayPick(ray, uniformResult);

	if (uniformResult.hit && uniformResult.distanceSquared < bestDistance) {
		best = m_uniformScaleHandle;
		bestDistance = xResult.distanceSquared;
	}

	if (best == m_uniformScaleHandle)
		return reGizmoAxis::ALL;
	else
		return reGizmoAxis::NONE;
}

void reScaleGizmo::HighlightAxis(reGizmoAxis axis) {
	rProp* handle = nullptr;

	switch (axis) {
	case reGizmoAxis::ALL:
		handle = m_uniformScaleHandle;
	};

	if (handle) {
		handle->GetModelInstance()->GetTriangleMeshInstanceMaterial(0)->SetDiffuseColor(rColor(255, 255, 0, 255));
	}
}

void reScaleGizmo::UnhighlightAxis(reGizmoAxis axis) {
	switch (axis) {
	case reGizmoAxis::ALL:
		m_uniformScaleHandle->GetModelInstance()->GetTriangleMeshInstanceMaterial(0)->SetDiffuseColor(rColor(130, 130, 130, 255));
		break;
	};
}