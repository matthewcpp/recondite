#include "platform/sdl/rSDLApplication.hpp"
#include "ModelViewerModule.hpp"

class ModelViewerApplication : public rApplication {
public:
	rModule* CreateModule(rEngine* engine);
};

rModule* ModelViewerApplication::CreateModule(rEngine* engine) {
	return new ModelViewerModule(engine);
}

IMPLEMENT_MAIN(ModelViewerApplication)