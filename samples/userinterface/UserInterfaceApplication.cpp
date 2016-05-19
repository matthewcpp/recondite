#include "platform/sdl/rSDLApplication.hpp"
#include "UserInterfaceModule.hpp"

class UserInterfaceApplication : public rApplication {
public:
	rModule* CreateModule(rEngine* engine);
};

rModule* UserInterfaceApplication::CreateModule(rEngine* engine) {
	return new UserInterfaceModule(engine);
}

IMPLEMENT_MAIN(UserInterfaceApplication)