#pragma once

#include "rEngine.hpp"

#include "ui/ruiOverlay.hpp"
#include "ui/ruiController.hpp"

class UserInterfaceController : public ruiController{
public:
	UserInterfaceController(const rString& name, rEngine* engine, ruiOverlay* overlay);
	virtual void OnOverlayLoaded();

private:
	rEngine* _engine;
	ruiOverlay* _overlay;
};