#include "rProp.hpp"

rProp::rProp(rModel* model, const rString& id, rEngine* engine)
	:rActor3(id, engine)
{
	m_model = model;
	m_drawable.reset(new rDrawable());
}

rString rProp::ClassName() const{
	return "Prop";
}

rModel* rProp::Model(){
	return m_model;
}

void rProp::SetModel(rModel* model){
	m_model = model;
}
void rProp::Draw(){
	rMatrix4& transform = TransformMatrix();

	if (this->Drawable()->Visible())
		m_engine->renderer->RenderModel(m_model, transform);
}

void rProp::DoRecalculateBoundingVolume() {
	rAlignedBox3 modelBounding = m_model->BoundingBox();
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