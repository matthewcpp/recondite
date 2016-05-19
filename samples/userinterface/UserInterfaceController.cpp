#include "UserInterfaceController.hpp"

UserInterfaceController::UserInterfaceController(const rString& name, rEngine* engine, ruiOverlay* overlay)
	:ruiController(name)
{
	_engine = engine;
	_overlay = overlay;
}

void UserInterfaceController::OnOverlayLoaded(){

}