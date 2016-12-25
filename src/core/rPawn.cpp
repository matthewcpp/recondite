#include "rPawn.hpp"

rPawn::rPawn(recondite::Model* model, const rString& id , rEngine* engine)
:rDrawable(id, engine)
{
	SetModel(model);
	m_animationController.SetSkeleton(model->GetSkeleton());
}

void rPawn::SetModel(recondite::Model* model){
	rDrawable::SetModel(model);
	
	if (model)
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
