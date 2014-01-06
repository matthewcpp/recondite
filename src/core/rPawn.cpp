#include "rPawn.hpp"

rPawn::rPawn(rModel* model, const rString& name , const rVector3& position)
:rActor3(name, position)
{
	SetModel(model);
}

rModel* rPawn::Model() const{
	return m_model;
}

void rPawn::SetModel(rModel* model){
	m_model = model;
	
	if (model)
		m_animationPlayer.SetSkeleton(model->Skeleton());
	else
		m_animationPlayer.SetSkeleton(NULL);
}
	
rAnimationPlayer* rPawn::AnimationPlayer(){
	return &m_animationPlayer;
}

int rPawn::Update(rEngine& engine){
	m_animationPlayer.Update(engine.time);

	return 0;
}

void rPawn::Draw(rEngine& engine){
	if (m_model){
		rMatrix4 transform;
		engine.renderer->RenderModel(m_model, transform);
	}
}
