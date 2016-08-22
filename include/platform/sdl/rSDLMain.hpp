#ifndef R_SDLMAIN_HPP
#define R_SDLMAIN_HPP

#include "SDL.h"

#define IMPLEMENT_MAIN(APPLICATION_TYPE) \
	int main(int argc, char** argv) {	\
		APPLICATION_TYPE app;	\
		app.SetArgs(argc, argv); \
		app.Init();		\
		SDL_Event event;	\
		while (app.IsReady()){	\
			while (SDL_PollEvent(&event)){	\
				app.ProcessEvent(event);	\
			}	\
			app.Tick();		\
			SDL_Delay(1);	\
		}	\
		app.Uninit();	\
		return 0;	\
	}	

#endif