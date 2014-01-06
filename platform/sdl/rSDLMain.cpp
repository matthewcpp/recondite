#include "SDL.h"

#include "rSDLApplication.hpp"

int main(int argc, char** argv){

	rSDLApplication app;
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

	return 0;
}