#include "reTranslateGizmo.hpp"

#include "primitive/rPrimitiveGeometry.hpp"

reTranslateGizmo::reTranslateGizmo(reComponent* component) 
	:reTransformGizmoBase(component)
{
	component->GetScene()->Bind(rEVT_SCENE_CLEAR, this, &reTranslateGizmo::OnSceneClear);
}

reGizmoAxis reTranslateGizmo::PickAxis(const rRay3& ray) {
	rPickResult xResult, yResult, zResult;
	rActor3* best = nullptr;
	float bestDistance = FLT_MAX;

	m_xHandle->RayPick(ray, xResult);
	m_yHandle->RayPick(ray, yResult);
	m_zHandle->RayPick(ray, zResult);

	if (xResult.hit && xResult.distanceSquared < bestDistance) {
		best = m_xHandle;
		bestDistance = xResult.distanceSquared;
	}

	if (yResult.hit && yResult.distanceSquared < bestDistance) {
		best = m_yHandle;
		bestDistance = yResult.distanceSquared;
	}

	if (zResult.hit && zResult.distanceSquared < bestDistance) {
		best = m_zHandle;
		bestDistance = zResult.distanceSquared;
	}

	if (best == m_xHandle)
		return reGizmoAxis::X;
	else if (best == m_yHandle)
		return reGizmoAxis::Y;
	else if (best == m_zHandle)
		return reGizmoAxis::Z;
	else
		return reGizmoAxis::NONE;
}

void reTranslateGizmo::Update(){
	if (!m_xHandle)
		CreateGeometry();

	//the origin of the gizmo should be in the center of the selection
	const wxArrayString& selection = m_component->SelectionManager()->GetSelection();

	if (selection.size() == 0){
		SetVisibility(false);
	}
	else{
		rScene* scene = m_component->GetScene();
		rAlignedBox3 selectionBounding, actorBounding;

		for (size_t i = 0; i < selection.size(); i++){
			rActor3* actor = scene->GetActor(selection[i].c_str().AsChar());
			actorBounding = actor->WorldBounding();
			selectionBounding.AddBox(actorBounding);
		}

		rVector3 gizmoPosition = selectionBounding.Center();
		gizmoPosition.y = selectionBounding.min.y;
		SetPosition(gizmoPosition);
		SetVisibility(true);
	}
}

using namespace recondite;

void reTranslateGizmo::CreateGeometry(){
	const rString TRANSLATE_GIZMO_HANDLE_NAME = "__translate_gizmo_handle__";
	rEngine* engine = m_component->GetEngine();
	
	recondite::Model* handleModel = engine->content->Models()->Get(TRANSLATE_GIZMO_HANDLE_NAME);

	if (!handleModel) {
		recondite::ModelData modelData;
		rPrimitiveGeometry::rPrimitiveCylinderParams cylinderParams(0.3f, 7, 20);
		rPrimitiveGeometry::CreateCylinder(cylinderParams, modelData);

		recondite::GeometryData* geometryData = modelData.GetGeometryData();
		size_t vertexOffset = geometryData->VertexCount();

		rPrimitiveGeometry::rPrimitiveConeParams coneParams(1.0, 2.5, 20);
		rPrimitiveGeometry::CreateCone(coneParams, modelData);

		rMatrix4 transform;
		transform.SetTranslate(0.0f, cylinderParams.height, 0.0f);

		geometryData->TransformVertices(vertexOffset, geometryData->VertexCount() - vertexOffset, transform);

		while (modelData.GetLineMeshCount() > 0) {
			modelData.DeleteLineMesh(modelData.GetLineMeshCount() - 1);
		}

		modelData.CalculateBoundings();

		handleModel = engine->content->Models()->LoadFromData(modelData, TRANSLATE_GIZMO_HANDLE_NAME);
	}

	m_xHandle = new reGizmoHandle(handleModel, "__translate_x_handle__", engine);
	m_xHandle->SetRotation(rVector3(0.0, 0.0f, -90.0f));
	m_xHandle->GetModelInstance()->GetTriangleMeshInstanceMaterial(0)->SetDiffuseColor(rColor::Red);
	m_xHandle->SetPickable(false);
	m_xHandle->SetShouldPersist(false);

	m_yHandle = new reGizmoHandle(handleModel, "__translate_y_handle__", engine);
	m_yHandle->GetModelInstance()->GetTriangleMeshInstanceMaterial(0)->SetDiffuseColor(rColor::Green);
	m_yHandle->SetPickable(false);
	m_yHandle->SetShouldPersist(false);

	m_zHandle = new reGizmoHandle(handleModel, "__translate_z_handle__", engine);
	m_zHandle->SetRotation(rVector3(90.0, 0.0f, 0.0f));
	m_zHandle->GetModelInstance()->GetTriangleMeshInstanceMaterial(0)->SetDiffuseColor(rColor::Blue);
	m_zHandle->SetPickable(false);
	m_zHandle->SetShouldPersist(false);

	engine->scene->AddActor(m_xHandle);
	engine->scene->AddActor(m_yHandle);
	engine->scene->AddActor(m_zHandle);
}