#include "reTranslateGizmo.hpp"

#include "primitive/rPrimitiveGeometry.hpp"

class reGizmoHandle : public rProp {
public: 
	reGizmoHandle(recondite::Model* model, const rString& id, rEngine* engine);

public:
	virtual void Draw() override;
};

reGizmoHandle::reGizmoHandle(recondite::Model* model, const rString& id, rEngine* engine)
	:rProp(model, id, engine)
{
	RenderingOptions()->SetLayer(1);
}

void reGizmoHandle::Draw() {
	rRenderMode renderMode = m_engine->renderer->GetModelRenderMode();
	m_engine->renderer->SetModelRenderMode(rRenderMode::Shaded);

	rProp::Draw();

	m_engine->renderer->SetModelRenderMode(renderMode);
}


reTranslateGizmo::reTranslateGizmo(reComponent* component){
	m_component = component;

	m_xHandle = nullptr;
	m_yHandle = nullptr;
	m_zHandle = nullptr;
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

void reTranslateGizmo::SetVisibility(bool visibility){
	m_xHandle->RenderingOptions()->SetVisibility(visibility);
	m_yHandle->RenderingOptions()->SetVisibility(visibility);
	m_zHandle->RenderingOptions()->SetVisibility(visibility);
}

void reTranslateGizmo::SetPosition(const rVector3& pos){
	m_currentPosition = pos;

	m_xHandle->SetPosition(pos);
	m_yHandle->SetPosition(pos);
	m_zHandle->SetPosition(pos);
}

rVector3 reTranslateGizmo::GetPosition(){
	return m_currentPosition;
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

		SetPosition(selectionBounding.Center());
		SetVisibility(true);
	}
}

using namespace recondite;

void reTranslateGizmo::CreateGeometry(){
	rEngine* engine = m_component->GetEngine();
	recondite::ModelData modelData;
	rPrimitiveGeometry::rPrimitiveCylinderParams params(0.5f, 5, 20);
	rPrimitiveGeometry::CreateCylinder(params, modelData);

	while (modelData.GetLineMeshCount() > 0) {
		modelData.DeleteLineMesh(modelData.GetLineMeshCount() - 1);
	}

	modelData.CalculateBoundings();

	recondite::Model* handleModel = engine->content->Models()->LoadFromData(modelData, "__translate_gizmo_handle__");

	m_xHandle = new reGizmoHandle(handleModel, "__translate_x_handle__", engine);
	m_xHandle->SetRotation(rVector3(0.0, 0.0f, -90.0f));
	m_xHandle->GetModelInstance()->GetTriangleMeshInstanceMaterial(0)->SetDiffuseColor(rColor::Red);
	m_xHandle->SetPickable(false);

	m_yHandle = new reGizmoHandle(handleModel, "__translate_y_handle__", engine);
	m_yHandle->GetModelInstance()->GetTriangleMeshInstanceMaterial(0)->SetDiffuseColor(rColor::Green);
	m_yHandle->SetPickable(false);

	m_zHandle = new reGizmoHandle(handleModel, "__translate_z_handle__", engine);
	m_zHandle->SetRotation(rVector3(90.0, 0.0f, 0.0f));
	m_zHandle->GetModelInstance()->GetTriangleMeshInstanceMaterial(0)->SetDiffuseColor(rColor::Blue);
	m_zHandle->SetPickable(false);

	engine->scene->AddActor(m_xHandle);
	engine->scene->AddActor(m_yHandle);
	engine->scene->AddActor(m_zHandle);
}

void reTranslateGizmo::HighlightAxis(reGizmoAxis axis) {
	rProp* handle = nullptr;

	switch (axis) {
		case reGizmoAxis::X:
			handle = m_xHandle;
			break;

		case reGizmoAxis::Y:
			handle = m_yHandle;
			break;

		case reGizmoAxis::Z:
			handle = m_zHandle;
			break;
	};

	if (handle) {
		handle->GetModelInstance()->GetTriangleMeshInstanceMaterial(0)->SetDiffuseColor(rColor(255,255,0,255));
	}
}

void reTranslateGizmo::UnhighlightAxis(reGizmoAxis axis) {
	switch (axis) {
	case reGizmoAxis::X:
		m_xHandle->GetModelInstance()->GetTriangleMeshInstanceMaterial(0)->SetDiffuseColor(rColor::Red);
		break;

	case reGizmoAxis::Y:
		m_yHandle->GetModelInstance()->GetTriangleMeshInstanceMaterial(0)->SetDiffuseColor(rColor::Green);
		break;

	case reGizmoAxis::Z:
		m_zHandle->GetModelInstance()->GetTriangleMeshInstanceMaterial(0)->SetDiffuseColor(rColor::Blue);
		break;
	};
}