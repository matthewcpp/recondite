#include "SDL.h"

#include "rSDLApplication.hpp"
#include "rDemoModule.hpp"

#include "log/rLogFile.hpp"

int main(int argc, char** argv){

	rDemoModule* demoModule = new rDemoModule();

	rLog::SetLogTarget(new rLogFile("recondite.log"));
	rLog::Info("Application Start");

	rSDLApplication app(demoModule);
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

	delete demoModule;

	return 0;
}