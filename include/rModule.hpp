#ifndef R_MODULE_HPP
#define R_MODULE_HPP

#include "rBuild.hpp"

#include "rEngine.hpp"
#include "ui/ruiOverlayManager.hpp"
#include "rScene.hpp"

class RECONDITE_API rModule {
public:

	virtual void Update(rEngine& engine) = 0;
	virtual void Draw(rEngine& engine) =0;
	virtual void Init(rEngine& engine) = 0;
	virtual void InitUI(ruiOverlayManager& manager, rEngine& engine) = 0;
	virtual void Uninit(rEngine& engine) = 0;
	virtual void LoadScene(const rString& sceneName, rScene* scene, rEngine& engine) = 0;
	virtual void DeleteActor(rActor3* actor) = 0;

};


#endif