#ifndef R_MODULE_HPP
#define R_MODULE_HPP

#include "rBuild.hpp"

#include "rEngine.hpp"
#include "ui/ruiManager.hpp"
#include "rScene.hpp"

namespace recondite {
	class RECONDITE_API Module {
	public:
		Module(const rString& name) { m_moduleName = name; }
		rString GetModuleName() const { return m_moduleName; }

		virtual void BeforeUpdateScene() {};
		virtual void AfterUpdateScene() {};

		virtual void BeforeRenderScene(rViewport* viewInfo) {};
		virtual void AfterRenderScene(rViewport* viewInfo) {};

		virtual void BeforeRenderUi(rViewport* viewInfo) {}
		virtual void AfterRenderUi(rViewport* viewInfo) {}

		virtual void Init(const rArrayString& args) {};
		virtual void Uninit() {};
		virtual void LoadScene(const rString& sceneName) = 0;
		virtual void DeleteActor(rActor3* actor) = 0;

	private:
		rString m_moduleName;
	};
}




#endif