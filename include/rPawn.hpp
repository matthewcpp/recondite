#ifndef R_PAWN_HPP
#define R_PAWN_HPP

#include "rBuild.hpp"
#include "rActor3.hpp"
#include "rAnimationController.hpp"
#include "asset/rModel.hpp"

class RECONDITE_API rPawn : public rActor3{
public:
	rPawn(recondite::Model* model, const rString& id , rEngine* engine);
	
public:
	Model* Model() const;
	void SetModel(recondite::Model* model);
	
	inline recondite::AnimationController* AnimationController();

	virtual rString ClassName() const;
	
	virtual int Update();
	virtual void Draw();
	
private:
	recondite::Model* m_model;
	recondite::AnimationController m_animationController;
};

inline recondite::AnimationController* rPawn::AnimationController() {
	return &m_animationController;
}

#endif
