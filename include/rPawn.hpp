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
	inline recondite::AnimationController* AnimationController();

	virtual void SetModel(recondite::Model* model) override;

	virtual rString ClassName() const;
	
	virtual void Update();
	virtual void Draw();

public:
	virtual size_t GetNumAssets() const override;
	virtual bool GetAsset(size_t index, rAssetType& assetType, rString& name) const override;
	
private:
	recondite::AnimationController m_animationController;

	rNO_COPY_CLASS(rPawn)
};

inline recondite::AnimationController* rPawn::AnimationController() {
	return &m_animationController;
}

#endif
