#include "rProp.hpp"
#include "rStaticMeshBoundingVolume.hpp"

rProp::rProp(recondite::Model* model, const rString& id, rEngine* engine)
	:rDrawable(id, engine)
{
	SetModel(model);
}

rString rProp::ClassName() const{
	return "Prop";
}

void rProp::Draw(){
	if (m_renderingOptions.GetVisibility()) {
		rMatrix4& transform = TransformMatrix();

		m_engine->renderer->RenderModel(_modelInstance.get(), transform);
	}
}

void rProp::SetModel(recondite::Model* model) {
	rDrawable::SetModel(model);
	SetBoundingVolume(new rStaticMeshBoundingVolume(model));
}