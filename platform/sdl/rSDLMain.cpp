#include "SDL.h"

#include "rSDLApplication.hpp"

#include "log/rLogFile.hpp"

int main(int argc, char** argv){

	rLog::SetLogTarget(new rLogFile("recondite.log"));
	rLog::Info("SDL Application Start");

	if (argc < 2){
		rLog::Error("No module specified");
		return 1;
	}

	rSDLApplication app;
	bool loaded = app.LoadModule("modelviewer.rec");

	if (!loaded){
		return 1;
	}

	app.SetDisplaySize(1024, 768);
	app.Init();

	SDL_Event event;

	while (app.IsRunning()){

		while (SDL_PollEvent(&event)){
			app.ProcessEvent(event);
		}

		app.Tick();
		SDL_Delay(1);
	}

	rLog::Info("Application Shutdown");

	app.Uninit();

	return 0;
}