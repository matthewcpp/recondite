#include "rPawn.hpp"

rPawn::rPawn(recondite::Model* model, const rString& id , rEngine* engine)
:rDrawable(model, id, engine)
{
	m_renderingOptions.reset(new rRenderingOptions());
	m_animationController.SetSkeleton(_model->GetSkeleton());
}

void rPawn::SetModel(recondite::Model* model){
	_model = model;
	
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
	if (_model){
		rMatrix4 transform;
		m_engine->renderer->RenderAnimatedModel(_model, transform, &m_animationController);
	}
}
