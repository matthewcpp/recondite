#include "ui/ruiController.hpp"

struct ruiController::Impl{
	ruiOverlay* overlay;
};

ruiController::ruiController(ruiOverlay* overlay){
	_impl = new Impl();
	_impl->overlay = overlay;
}

ruiController::~ruiController(){
	delete _impl;
}

ruiOverlay* ruiController::GetOverlay(){
	return _impl->overlay;
}

void ruiController::OnOverlayLoaded(){}