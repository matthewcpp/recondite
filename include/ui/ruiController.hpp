#ifndef RUI_CONTROLLER_HPP
#define RUI_CONTROLLER_HPP

#include "rEvent.hpp"
#include "ui/ruiOverlay.hpp"

class ruiController{
public:
	ruiController(ruiOverlay* overlay);
	~ruiController();

	virtual void OnOverlayLoaded();
	ruiOverlay* GetOverlay();

private:
	struct Impl;
	Impl* _impl;
};

#endif