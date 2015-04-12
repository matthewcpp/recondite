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
