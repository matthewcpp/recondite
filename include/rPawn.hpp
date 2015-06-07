#ifndef R_PAWN_HPP
#define R_PAWN_HPP

#include "rBuild.hpp"
#include "rActor3.hpp"
#include "rAnimationPlayer.hpp"
#include "asset/rModel.hpp"

class RECONDITE_API rPawn : public rActor3{
public:
	rPawn(rModel* model, const rString& id , rEngine* engine);
	
public:
	rModel* Model() const;
	void SetModel(rModel* model);
	
	rAnimationPlayer* AnimationPlayer();
	
	virtual int Update();
	virtual void Draw();
	
private:
	rModel* m_model;
	rAnimationPlayer m_animationPlayer;
};

#endif
