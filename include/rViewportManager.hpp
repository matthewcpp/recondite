#pragma once

#include "rBuild.hpp"

#include "rViewport.hpp"
#include "rString.hpp"

namespace recondite {
	class RECONDITE_API ViewportManager {
	public:
		ViewportManager();
		~ViewportManager();

	public:
		rViewport* CreateViewport(const rString& name);

		rViewport* GetViewport(size_t index);
		rViewport* GetViewportByName(const rString& name);
		size_t NumViewports() const;

		void DeleteViewportByName(const rString& name);
		void DeleteViewport(size_t index);

		void SetActiveViewport(rViewport* viewport);
		rViewport* GetActiveViewport();

	private:
		struct Impl;
		Impl* _impl;
	};
}
