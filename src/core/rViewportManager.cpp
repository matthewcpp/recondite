#include "rViewportManager.hpp"

#include <vector>
#include <memory>

namespace recondite {
	struct ViewportManager::Impl {
		rViewport* activeViewport;
		std::vector <std::unique_ptr<rViewport>> viewports;

		Impl() : activeViewport(nullptr) {}
	};

	ViewportManager::ViewportManager() {
		_impl = new Impl();
	}

	ViewportManager::~ViewportManager() {
		delete _impl;
	}

	rViewport* ViewportManager::CreateViewport(const rString& name) {
		rViewport* viewport = new rViewport(name);
		viewport->SetScreenRect(0, 0, 1024, 768);

		_impl->viewports.emplace_back(viewport);

		return viewport;
	}

	rViewport* ViewportManager::GetViewport(size_t index) {
		return _impl->viewports[index].get();
	}

	rViewport* ViewportManager::GetViewportByName(const rString& name) {
		for (size_t i = 0; i < _impl->viewports.size(); i++) {
			rViewport* viewport = _impl->viewports[i].get();

			if (viewport->Name() == name)
				return viewport;
		}

		return nullptr;
	}

	size_t ViewportManager::NumViewports() const {
		return _impl->viewports.size();
	}

	void ViewportManager::DeleteViewportByName(const rString& name) {
		for (size_t i = 0; i < _impl->viewports.size(); i++) {
			rViewport* viewport = _impl->viewports[i].get();

			if (viewport->Name() == name) {
				_impl->viewports.erase(_impl->viewports.begin() + i);
				return;
			}
		}
	}

	void ViewportManager::DeleteViewport(size_t index) {
		auto it = _impl->viewports.begin();
		std::advance(it, index);

		_impl->viewports.erase(it);
	}

	void ViewportManager::SetActiveViewport(rViewport* viewport) {
		_impl->activeViewport = viewport;
	}

	rViewport* ViewportManager::GetActiveViewport() {
		return _impl->activeViewport;
	}
}