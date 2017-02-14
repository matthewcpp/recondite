#include "platform/sdl/rSDLApplication.hpp"
#include "../Game.hpp"

class Application : public rApplication {
public:
	recondite::Module* CreateModule(rEngine* engine);
};

recondite::Module* Application::CreateModule(rEngine* engine) {
	return new Game(engine);
}

IMPLEMENT_MAIN(Application)