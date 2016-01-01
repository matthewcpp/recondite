#ifndef R_MODULE_HPP
#define R_MODULE_HPP

#include "rBuild.hpp"

#include "rEngine.hpp"
#include "ui/ruiOverlayManager.hpp"
#include "rScene.hpp"
#include "rViewInfo.hpp"

class RECONDITE_API rModule {
public:
	rModule(const rString& name);

public:

	rString GetModuleName() const;

	virtual void BeforeUpdateScene() {};
	virtual void AfterUpdateScene() {};
	
	virtual void BeforeRenderScene(rViewInfo* viewInfo) {};
	virtual void AfterRenderScene(rViewInfo* viewInfo) {};

	virtual void Init() {};
	virtual void Uninit() {};
	virtual void LoadScene(const rString& sceneName) = 0;
	virtual void DeleteActor(rActor3* actor) = 0;

private:
	rString m_moduleName;
};


#endif