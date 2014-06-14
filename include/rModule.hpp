#ifndef R_MODULE_HPP
#define R_MODULE_HPP

#include "rBuild.hpp"

#include "rEngine.hpp"
#include "ui/ruiOverlayManager.hpp"
#include "rScene.hpp"
#include "rViewInfo.hpp"

//modules need to export 2 methods in order for them to be loaded by the DLL loader classes
#ifdef _MSC_VER
	#define RECONDITE_MODULE_INTERFACE __declspec(dllexport)
#else
	#define RECONDITE_MODULE_INTERFACE
#endif

class RECONDITE_API rModule {
public:

	virtual void BeforeUpdateScene(rEngine& engine) = 0;
	virtual void AfterUpdateScene(rEngine& engine) = 0;
	
	virtual void BeforeRenderScene(rViewInfo& view, rEngine& engine) = 0;
	virtual void AfterRenderScene(rViewInfo& view, rEngine& engine) = 0;

	virtual void BeforeRenderOverlay(rViewInfo& view, rEngine& engine) = 0;
	virtual void AfterRenderOverlay(rViewInfo& view, rEngine& engine) = 0;

	virtual void Init(rEngine& engine) = 0;
	virtual void InitUI(ruiOverlayManager& manager, rEngine& engine) = 0;
	virtual void Uninit(rEngine& engine) = 0;
	virtual void LoadScene(const rString& sceneName, rEngine& engine) = 0;
	virtual void DeleteActor(rActor3* actor) = 0;

};


#endif