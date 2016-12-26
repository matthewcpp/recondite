#include "platform/sdl/rSDLApplication.hpp"
#include "SelectionModule.hpp"

class SelectionApplication : public rApplication {
public:
	rModule* CreateModule(rEngine* engine);
};

rModule* SelectionApplication::CreateModule(rEngine* engine) {
	return new SelectionModule(engine);
}

IMPLEMENT_MAIN(SelectionApplication)