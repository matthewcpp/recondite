#ifndef R_SDLMAIN_HPP
#define R_SDLMAIN_HPP

#include "SDL.h"

#include "log/rLogFile.hpp"
#include "log/rLogStdOut.hpp"
#include "log/rLogChain.hpp"

#define IMPLEMENT_MAIN(APPLICATION_TYPE) \
	int main(int argc, char** argv) {	\
		rLogChain* logChain = new rLogChain(new rLogFile("recondite.log"), new rLogStdOut());	\
		rLog::SetLogTarget(logChain);	\
		rLog::Info("SDL Application Start"); \
		APPLICATION_TYPE app;	\
		app.SetDisplaySize(1024, 768);	\
		app.Init();		\
		SDL_Event event;	\
		while (app.IsReady()){	\
			while (SDL_PollEvent(&event)){	\
				app.ProcessEvent(event);	\
			}	\
			app.Tick();		\
			SDL_Delay(1);	\
		}	\
		rLog::Info("Application Shutdown");		\
		app.Uninit();	\
		return 0;	\
	}	

#endif