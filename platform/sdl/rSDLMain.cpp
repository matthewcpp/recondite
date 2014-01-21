#include "SDL.h"

#include "rSDLApplication.hpp"
#include "rDemoModule.hpp"

int main(int argc, char** argv){

	rDemoModule* demoModule = new rDemoModule();

	rSDLApplication app(demoModule);
	app.Init();

	SDL_Event event;

	while (app.IsRunning()){

		while (SDL_PollEvent(&event)){
			app.ProcessEvent(event);
		}

		app.Tick();
		SDL_Delay(1);
	}

	app.Uninit();

	delete demoModule;

	return 0;
}