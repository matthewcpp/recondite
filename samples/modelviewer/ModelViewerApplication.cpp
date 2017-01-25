#include "platform/sdl/rSDLApplication.hpp"
#include "ModelViewerModule.hpp"

class ModelViewerApplication : public rApplication {
public:
	recondite::Module* CreateModule(rEngine* engine);
};

recondite::Module* ModelViewerApplication::CreateModule(rEngine* engine) {
	return new ModelViewerModule(engine);
}

IMPLEMENT_MAIN(ModelViewerApplication)