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
	
	/*
	if (model)
		m_animationPlayer.SetSkeleton(model->Skeleton());
	else
		m_animationPlayer.SetSkeleton(NULL);
	*/
}
	
rAnimationPlayer* rPawn::AnimationPlayer(){
	return &m_animationPlayer;
}

int rPawn::Update(){
	m_animationPlayer.Update(m_engine->time);

	return 0;
}

void rPawn::Draw(){
	if (m_model){
		rMatrix4 transform;
		//m_engine->renderer->RenderModel(m_model, RenderingOptions(), transform);
	}
}
