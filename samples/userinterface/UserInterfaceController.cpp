#include "UserInterfaceController.hpp"

UserInterfaceController::UserInterfaceController(const rString& name, rEngine* engine, ruiDocument* document)
	:ruiController(name)
{
	_engine = engine;
	_document = document;
}

void UserInterfaceController::OnDocumentLoaded(){

}