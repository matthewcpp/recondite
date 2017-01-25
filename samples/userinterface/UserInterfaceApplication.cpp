#include "platform/sdl/rSDLApplication.hpp"
#include "UserInterfaceModule.hpp"

class UserInterfaceApplication : public rApplication {
public:
	recondite::Module* CreateModule(rEngine* engine);
};

recondite::Module* UserInterfaceApplication::CreateModule(rEngine* engine) {
	return new UserInterfaceModule(engine);
}

IMPLEMENT_MAIN(UserInterfaceApplication)