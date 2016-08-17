#ifndef R_PAWN_HPP
#define R_PAWN_HPP

#include "rBuild.hpp"
#include "rActor3.hpp"
#include "rAnimationPlayer.hpp"
#include "asset/rModel.hpp"

class RECONDITE_API rPawn : public rActor3{
public:
	rPawn(recondite::Model* model, const rString& id , rEngine* engine);
	
public:
	Model* Model() const;
	void SetModel(recondite::Model* model);
	
	rAnimationPlayer* AnimationPlayer();
	
	virtual int Update();
	virtual void Draw();
	
private:
	recondite::Model* m_model;
	rAnimationPlayer m_animationPlayer;
};

#endif
