#include "platform/sdl/rSDLApplication.hpp"
#include "SelectionModule.hpp"

class SelectionApplication : public rApplication {
public:
	recondite::Module* CreateModule(rEngine* engine);
};

recondite::Module* SelectionApplication::CreateModule(rEngine* engine) {
	return new SelectionModule(engine);
}

IMPLEMENT_MAIN(SelectionApplication)