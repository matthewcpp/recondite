#ifndef R_SDLINPUTMANAGER_HPP
#define R_SDLINPUTMANAGER_HPP

#include "SDL.h"

#include "rInputManager.hpp"

class rSDLInputManager : public rInputManager{
public:
	rSDLInputManager();
	void ProcessInputEvent(SDL_Event& event);

private:
	void ProcessMouseButtonEvent(rButtonState state, SDL_Event& event);
	void ProcessKeyboardEvent(rKeyState state, SDL_Event& event);
};

#endif