#include "tools/reScaleGizmo.hpp"

#include "asset/rModelData.hpp"
#include "primitive/rPrimitiveGeometry.hpp"
#include "reGizmo.hpp"

#define BOX_SIZE 2.5f
#define DEFAULT_STEM_LENGTH 7.0f

reScaleGizmoHandle::reScaleGizmoHandle(const rVector3& direction, recondite::Model* model, const rString& id, rEngine* engine)
:reGizmoHandle(model, id, engine)
{
	_direction = direction;
	_stemLength = DEFAULT_STEM_LENGTH;
}

inline void reScaleGizmoHandle::SetAnchor(const rVector3& anchor) {
	_anchor = anchor;
}

void reScaleGizmoHandle::UpdatePosition() {
	UpdateScale();

	SetPosition(_anchor + (_direction * (_stemLength * _scaleFactor)));
}

bool reScaleGizmoHandle::RayPick(const rRay3& ray, rPickResult& result) {
	UpdatePosition();

	return rProp::RayPick(ray, result);
}

void reScaleGizmoHandle::Draw() {
	if (RenderingOptions()->GetVisibility()) {
		UpdatePosition();

		reGizmoHandle::Draw();

		rAlignedBox3 worldBounding = WorldBounding();
		rImmediateBuffer stemBuffer(rGeometryType::Lines, 3, false);
		stemBuffer.PushVertex(_anchor);
		stemBuffer.PushVertex(worldBounding.Center());

		stemBuffer.PushIndex(0, 1);

		rColor stemColor = GetModelInstance()->GetTriangleMeshInstanceMaterial(0)->DiffuseColor();
		m_engine->renderer->RenderImmediateLines(stemBuffer, stemColor);
	}
}

void reScaleGizmoHandle::UpdateScale() {
	rVector3 updatedScale = rVector3::OneVector;

	rViewport* activeViewport = m_engine->component->GetActiveViewport();

	if (activeViewport) {
		float distance = _anchor.Distance(activeViewport->Camera()->GetPosition());
		distance /= 100.0f;
		updatedScale.Set(distance, distance, distance);

		_scaleFactor = distance;
	}

	SetScale(updatedScale);
}

reScaleGizmo::reScaleGizmo(reComponent* component) 
:reTransformGizmoBase(component)
{
	m_uniformScaleHandle = nullptr;
	component->GetScene()->Bind(rEVT_SCENE_CLEAR, this, &reScaleGizmo::OnSceneClear);
}

void reScaleGizmo::OnSceneClear(rEvent& event) {
	reTransformGizmoBase::OnSceneClear(event);
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

		rVector3 gizmoPosition = selectionBounding.Center();
		gizmoPosition.y = selectionBounding.min.y;
		SetPosition(gizmoPosition);
		SetVisibility(true);
	}
}
void reScaleGizmo::SetVisibility(bool visibility) {
	m_uniformScaleHandle->RenderingOptions()->SetVisibility(visibility);

	reTransformGizmoBase::SetVisibility(visibility);
}

void reScaleGizmo::CreateGeometry() {
	const rString SCALE_GIZMO_HANDLE_NAME = "__scale_gizmo_handle__";
	rEngine* engine = m_component->GetEngine();

	recondite::Model* handleModel = engine->content->Models()->Get(SCALE_GIZMO_HANDLE_NAME);
	if (!handleModel) {
		recondite::ModelData modelData;
		rPrimitiveGeometry::rPrimitiveBoxParams box;
		box.extents.Set(BOX_SIZE, BOX_SIZE, BOX_SIZE);
		rPrimitiveGeometry::CreateBox(box, modelData);

		rMatrix4 translateMatrix;
		translateMatrix.SetTranslate(0, -0.5, 0);

		recondite::GeometryData* geometryData = modelData.GetGeometryData();
		geometryData->TransformVertices(0, geometryData->VertexCount(), translateMatrix);

		while (modelData.GetLineMeshCount() > 0) {
			modelData.DeleteLineMesh(modelData.GetLineMeshCount() - 1);
		}

		modelData.CalculateBoundings();

		handleModel = engine->content->Models()->LoadFromData(modelData, "__scale_gizmo_handle__");
	}

	m_uniformScaleHandle = new reGizmoHandle(handleModel, "__scale_uniform_handle__", engine);
	m_uniformScaleHandle->GetModelInstance()->GetTriangleMeshInstanceMaterial(0)->SetDiffuseColor(rColor(130,130,130,255));
	FinalizeAndAddHandle(m_uniformScaleHandle);

	m_xHandle = new reScaleGizmoHandle(rVector3::RightVector, handleModel, "__scale_x_handle__", engine);
	m_xHandle->GetModelInstance()->GetTriangleMeshInstanceMaterial(0)->SetDiffuseColor(rColor::Red);
	FinalizeAndAddHandle(m_xHandle);

	m_yHandle = new reScaleGizmoHandle(rVector3::UpVector, handleModel, "__scale_y_handle__", engine);
	m_yHandle->GetModelInstance()->GetTriangleMeshInstanceMaterial(0)->SetDiffuseColor(rColor::Green);
	FinalizeAndAddHandle(m_yHandle);

	m_zHandle = new reScaleGizmoHandle(rVector3::BackwardVector, handleModel, "__scale_z_handle__", engine);
	m_zHandle->GetModelInstance()->GetTriangleMeshInstanceMaterial(0)->SetDiffuseColor(rColor::Blue);
	FinalizeAndAddHandle(m_zHandle);
}

void reScaleGizmo::SetPosition(const rVector3& position) {
	m_currentPosition = position;

	m_uniformScaleHandle->SetPosition(m_currentPosition);

	reinterpret_cast<reScaleGizmoHandle*>(m_xHandle)->SetAnchor(m_currentPosition);
	reinterpret_cast<reScaleGizmoHandle*>(m_yHandle)->SetAnchor(m_currentPosition);
	reinterpret_cast<reScaleGizmoHandle*>(m_zHandle)->SetAnchor(m_currentPosition);
}

void reScaleGizmo::ResetStems() {
	reinterpret_cast<reScaleGizmoHandle*>(m_uniformScaleHandle)->SetStemLength(DEFAULT_STEM_LENGTH);

	reinterpret_cast<reScaleGizmoHandle*>(m_xHandle)->SetStemLength(DEFAULT_STEM_LENGTH);
	reinterpret_cast<reScaleGizmoHandle*>(m_yHandle)->SetStemLength(DEFAULT_STEM_LENGTH);
	reinterpret_cast<reScaleGizmoHandle*>(m_zHandle)->SetStemLength(DEFAULT_STEM_LENGTH);
}

reGizmoAxis reScaleGizmo::PickAxis(const rRay3& ray) {
	rPickResult xResult, yResult, zResult, uniformResult;
	rActor3* best = nullptr;
	float bestDistance = FLT_MAX;

	m_uniformScaleHandle->RayPick(ray, uniformResult);
	m_xHandle->RayPick(ray, xResult);
	m_yHandle->RayPick(ray, yResult);
	m_zHandle->RayPick(ray, zResult);

	if (uniformResult.hit && uniformResult.distanceSquared < bestDistance) {
		best = m_uniformScaleHandle;
		bestDistance = xResult.distanceSquared;
	}

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

	if (best == m_uniformScaleHandle)
		return reGizmoAxis::ALL;
	else if (best == m_xHandle)
		return reGizmoAxis::X;
	else if (best == m_yHandle)
		return reGizmoAxis::Y;
	else if (best == m_zHandle)
		return reGizmoAxis::Z;
	else
		return reGizmoAxis::NONE;
}

void reScaleGizmo::HighlightAxis(reGizmoAxis axis) {
	if (axis == reGizmoAxis::ALL) {
		SetModelInstanceColor(m_uniformScaleHandle, rColor(255, 255, 0, 255));
	}
	else {
		reTransformGizmoBase::HighlightAxis(axis);
	}
}

void reScaleGizmo::UnhighlightAxis(reGizmoAxis axis) {
	if (axis == reGizmoAxis::ALL) {
		SetModelInstanceColor(m_uniformScaleHandle, rColor(130, 130, 130, 255));
	}
	else {
		reTransformGizmoBase::UnhighlightAxis(axis);
	}
}

reGizmoHandle* reScaleGizmo::GetHandle(reGizmoAxis axis) {
	if (axis == reGizmoAxis::ALL) {
		return m_uniformScaleHandle;
	}
	else {
		return reTransformGizmoBase::GetHandle(axis);
	}
}