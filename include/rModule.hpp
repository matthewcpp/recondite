#ifndef R_MODULE_HPP
#define R_MODULE_HPP

#include "rBuild.hpp"

#include "rEngine.hpp"
#include "ui/ruiManager.hpp"
#include "rScene.hpp"

namespace recondite {
	class RECONDITE_API Module {
	public:
		virtual void BeforeUpdateScene() {};
		virtual void AfterUpdateScene() {};

		virtual void BeforeRenderScene(rViewport* viewport) {};
		virtual void AfterRenderScene(rViewport* viewport) {};

		virtual void BeforeRenderUi(rViewport* viewport) {}
		virtual void AfterRenderUi(rViewport* viewport) {}

		virtual void Register(rEngine* engine) {}
		virtual void Init(const rArrayString& args) {};
		virtual void Uninit() {};
	};
}




#endif