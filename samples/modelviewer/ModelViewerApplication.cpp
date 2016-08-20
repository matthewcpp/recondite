#include "platform/sdl/rSDLApplication.hpp"
#include "ModelViewerModule.hpp"

class UserInterfaceApplication : public rApplication {
public:
	rModule* CreateModule(rEngine* engine);
};

rModule* UserInterfaceApplication::CreateModule(rEngine* engine) {
	return new ModelViewerModule(engine);
}

IMPLEMENT_MAIN(UserInterfaceApplication)