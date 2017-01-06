#include "tools/reGizmo.hpp"

#include "rMatrixUtil.hpp"

reGizmoHandle::reGizmoHandle(recondite::Model* model, const rString& id, rEngine* engine)
	:rProp(model, id, engine)
{
	RenderingOptions()->SetLayer(1);
	_renderModeOverride = rRenderMode::Shaded;
	_scaleFactor = 1.0f;
}

void reGizmoHandle::Draw() {
	UpdateScale();

	rRenderMode renderMode = m_engine->renderer->GetModelRenderMode();
	m_engine->renderer->SetModelRenderMode(_renderModeOverride);

	rProp::Draw();

	m_engine->renderer->SetModelRenderMode(renderMode);
}

size_t reGizmoHandle::GetNumAssets() const {
	return 0;
}

bool reGizmoHandle::GetAsset(size_t index, rAssetType& assetType, rString& name) {
	return false;
}

bool reGizmoHandle::RayPick(const rRay3& ray, rPickResult& result) {
	UpdateScale();

	return rProp::RayPick(ray, result);
}

void reGizmoHandle::UpdateScale() {
	rVector3 updatedScale = rVector3::OneVector;

	rViewport* activeViewport = m_engine->component->GetActiveViewport();

	if (activeViewport) {
		rVector3 center = WorldBounding().Center();
		float distance = center.Distance(activeViewport->Camera()->GetPosition());
		distance /= 100.0f;
		updatedScale.Set(distance, distance, distance);

		_scaleFactor = distance;
	}

	SetScale(updatedScale);
}

reTransformGizmoBase::reTransformGizmoBase(reComponent* component) {
	m_component = component;

	m_xHandle = nullptr;
	m_yHandle = nullptr;
	m_zHandle = nullptr;
}

reGizmoHandle* reTransformGizmoBase::GetHandle(reGizmoAxis axis) {
	switch (axis) {
	case reGizmoAxis::X:
		return m_xHandle;

	case reGizmoAxis::Y:
		return m_yHandle;

	case reGizmoAxis::Z:
		return m_zHandle;

	default:
		return nullptr;
	}
}

void reTransformGizmoBase::SetModelInstanceColor(rProp* handle, const rColor& color) {
	recondite::ModelInstance* modelInstance = handle->GetModelInstance();
	const recondite::Model* model = modelInstance->GetModel();

	for (size_t i = 0; i < model->GetTriangleMeshCount(); i++) {
		modelInstance->GetTriangleMeshInstanceMaterial(i)->SetDiffuseColor(color);
	}
	
	for (size_t i = 0; i < model->GetLineMeshCount(); i++) {
		modelInstance->GetLineMeshInstanceMaterial(i)->SetDiffuseColor(color);
	}
}

void reTransformGizmoBase::HighlightAxis(reGizmoAxis axis) {
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
		SetModelInstanceColor(handle, rColor(255, 255, 0, 255));
	}
}

void reTransformGizmoBase::UnhighlightAxis(reGizmoAxis axis) {
	switch (axis) {
	case reGizmoAxis::X:
		SetModelInstanceColor(m_xHandle, rColor::Red);
		break;

	case reGizmoAxis::Y:
		SetModelInstanceColor(m_yHandle, rColor::Green);
		break;

	case reGizmoAxis::Z:
		SetModelInstanceColor(m_zHandle, rColor::Blue);
		break;
	};
}

void reTransformGizmoBase::SetVisibility(bool visibility) {
	m_xHandle->RenderingOptions()->SetVisibility(visibility);
	m_yHandle->RenderingOptions()->SetVisibility(visibility);
	m_zHandle->RenderingOptions()->SetVisibility(visibility);
}

void reTransformGizmoBase::SetPosition(const rVector3& position) {
	m_currentPosition = position;

	m_xHandle->SetPosition(position);
	m_yHandle->SetPosition(position);
	m_zHandle->SetPosition(position);
}

rVector3 reTransformGizmoBase::GetPosition() const {
	return m_currentPosition;
}