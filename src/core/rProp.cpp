#include "rProp.hpp"
#include "rStaticMeshBoundingVolume.hpp"

rProp::rProp(recondite::Model* model, const rString& id, rEngine* engine)
	:rDrawable(id, engine)
{
	SetModel(model);
}

rProp::rProp(const rString& id, rEngine* engine)
	: rDrawable(id, engine)
{
	SetModel(nullptr);
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

	if (model) {
		SetBoundingVolume(new rStaticMeshBoundingVolume(model));
	}
}

bool rProp::DoSerialize(riSerializationTarget* target, rSerializeAction action) {
	target->Category("Prop");

	rString modelName;
	if (action == rSerializeAction::Save) {
		modelName = GetModelInstance()->GetModel()->GetName();
		target->String("model", modelName);
	}
	else {
		if (target->String("model", modelName)) {
			recondite::Model* model = m_engine->content->Models()->Get(modelName);
			SetModel(model);
		}
	}

	return rActor3::DoSerialize(target, action);
}

size_t rProp::GetNumAssets() const {
	return 1U;
}

bool rProp::GetAsset(size_t index, rAssetType& assetType, rString& name) const {
	if (index == 0) {
		assetType = rAssetType::Model;
		name = _modelInstance->GetModel()->GetName();
		return true;
	}
	else {
		return false;
	}
}