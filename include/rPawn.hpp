#ifndef R_PAWN_HPP
#define R_PAWN_HPP

#include "rBuild.hpp"
#include "rActor3.hpp"
#include "rAnimationPlayer.hpp"
#include "rModel.hpp"

class RECONDITE_API rPawn : public rActor3{
public:
	rPawn(rModel* model, const rString& name , const rVector3& position);
	
public:
	rModel* Model() const;
	void SetModel(rModel* model);
	
	rAnimationPlayer* AnimationPlayer();
	
	virtual int Update(rEngine& engine);
	virtual void Draw(rEngine& engine);
	
private:
	rModel* m_model;
	rAnimationPlayer m_animationPlayer;
};

#endif
