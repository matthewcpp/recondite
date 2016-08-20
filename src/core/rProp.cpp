#include "rProp.hpp"

rProp::rProp(recondite::Model* model, const rString& id, rEngine* engine)
	:rActor3(id, engine)
{
	m_model = model;
	m_renderingOptions.reset(new rRenderingOptions());
}

rString rProp::ClassName() const{
	return "Prop";
}

recondite::Model* rProp::Model(){
	return m_model;
}

void rProp::SetModel(recondite::Model* model){
	m_model = model;
}
void rProp::Draw(){
	rMatrix4& transform = TransformMatrix();

	m_engine->renderer->RenderModel(m_model, transform);
}

void rProp::DoRecalculateBoundingVolume() {
	rAlignedBox3 modelBounding = m_model->GetBoundingBox();
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