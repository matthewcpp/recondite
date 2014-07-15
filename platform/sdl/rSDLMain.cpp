#include "SDL.h"

#include "rSDLApplication.hpp"

#include "log/rLogFile.hpp"
#include "log/rLogStdOut.hpp"
#include "log/rLogChain.hpp"

int main(int argc, char** argv){
	rLogChain* logChain = new rLogChain(new rLogFile("recondite.log"), new rLogStdOut());
	rLog::SetLogTarget(logChain);
	rLog::Info("SDL Application Start");

	if (argc < 2){
		rLog::Error("No module specified");
		return 1;
	}

	rString moduleName(argv[1]);

	rSDLApplication app;
	bool loaded = app.LoadModule(moduleName);

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