#include "rPawn.hpp"

rPawn::rPawn(recondite::Model* model, const rString& id , rEngine* engine)
:rActor3(id, engine)
{
	SetModel(model);
	m_renderingOptions.reset(new rRenderingOptions());
}

Model* rPawn::Model() const{
	return m_model;
}

void rPawn::SetModel(recondite::Model* model){
	m_model = model;
	
	if (model)
		m_animationController.SetSkeleton(model->GetSkeleton());

}

int rPawn::Update(){
	m_animationController.Update(m_engine->time);

	return 0;
}

rString rPawn::ClassName() const {
	return "Pawn";
}

void rPawn::Draw(){
	if (m_model){
		rMatrix4 transform;
		m_engine->renderer->RenderAnimatedModel(m_model, transform, &m_animationController);
	}
}
