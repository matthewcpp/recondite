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

	virtual void BeforeUpdateScene() {};
	virtual void AfterUpdateScene() {};
	
	virtual void BeforeRenderScene(rViewInfo* viewInfo) {};
	virtual void AfterRenderScene(rViewInfo* viewInfo) {};

	virtual void Init() {};
	virtual void Uninit() {};
	virtual void LoadScene(const rString& sceneName) = 0;
	virtual void DeleteActor(rActor3* actor) = 0;
};


#endif