#ifndef R_PAWN_HPP
#define R_PAWN_HPP

#include "rBuild.hpp"
#include "rDrawable.hpp"
#include "rAnimationController.hpp"
#include "asset/rModel.hpp"

class RECONDITE_API rPawn : public rDrawable {
public:
	rPawn(recondite::Model* model, const rString& id , rEngine* engine);
	
public:
	virtual void SetModel(recondite::Model* model) override;
	
	inline recondite::AnimationController* AnimationController();

	virtual rString ClassName() const;
	
	virtual void Update();
	virtual void Draw();
	
private:
	recondite::AnimationController m_animationController;

	rNO_COPY_CLASS(rPawn)
};

inline recondite::AnimationController* rPawn::AnimationController() {
	return &m_animationController;
}

#endif
