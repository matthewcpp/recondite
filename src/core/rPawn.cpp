#include "rPawn.hpp"
#include "rStaticMeshBoundingVolume.hpp"

rPawn::rPawn(recondite::Model* model, const rString& id , rEngine* engine)
:rDrawable(id, engine)
{
	SetModel(model);
	m_animationController.SetSkeleton(model->GetSkeleton());
}

void rPawn::Update(){
	m_animationController.Update(m_engine->time);
}

rString rPawn::ClassName() const {
	return "Pawn";
}

void rPawn::Draw(){
	if (m_renderingOptions.GetVisibility()){
		rMatrix4 transform = TransformMatrix();
		m_engine->renderer->RenderAnimatedModel(_modelInstance.get(), transform, &m_animationController);
	}
}

void rPawn::SetModel(recondite::Model* model) {
	rDrawable::SetModel(model);
	m_animationController.SetSkeleton(model->GetSkeleton());

	//todo handle bounding for animated model
	SetBoundingVolume(new rStaticMeshBoundingVolume(model));
}

size_t rPawn::GetNumAssets() const {
	return 1U;
}

bool rPawn::GetAsset(size_t index, rAssetType& assetType, rString& name) const {
	if (index == 0) {
		assetType = rAssetType::Model;
		name = _modelInstance->GetModel()->GetName();
		return true;
	}
	else {
		return false;
	}
}