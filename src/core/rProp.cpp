#include "rProp.hpp"

rProp::rProp(recondite::Model* model, const rString& id, rEngine* engine)
	:rDrawable(id, engine)
{
	SetModel(model);
	m_renderingOptions.reset(new rRenderingOptions());
}

rString rProp::ClassName() const{
	return "Prop";
}

void rProp::Draw(){
	rMatrix4& transform = TransformMatrix();

	m_engine->renderer->RenderModel(_modelInstance.get(), transform);
}

void rProp::DoRecalculateBoundingVolume() {
	rAlignedBox3 modelBounding = _modelInstance->GetModel()->GetBoundingBox();
	const rMatrix4& transform = TransformMatrix();

	transform.TransformVector3(modelBounding.min);
	transform.TransformVector3(modelBounding.max);

	rAlignedBox3 transformedBounding;
	transformedBounding.AddPoint(modelBounding.min);
	transformedBounding.AddPoint(modelBounding.max);

	m_boundingVolume.SetBox(transformedBounding);
}

riBoundingVolume* rProp::DoGetBoundingVolume() {
	return &m_boundingVolume;
}