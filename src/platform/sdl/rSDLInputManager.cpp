#include "sdl/rSDLInputManager.hpp"

rSDLInputManager::rSDLInputManager()
{
}

void rSDLInputManager::ProcessInputEvent(SDL_Event& event){
	switch (event.type){
	case SDL_MOUSEMOTION:
		CreateMouseMotionEvent(event.motion.x, event.motion.y);
		break;

	case SDL_MOUSEBUTTONDOWN:
		ProcessMouseButtonEvent(rBUTTON_STATE_DOWN, event);
		break;

	case SDL_MOUSEBUTTONUP:
		ProcessMouseButtonEvent(rBUTTON_STATE_UP, event);
		break;

	case SDL_MOUSEWHEEL:
		ProcessWheelEvent(event);
		break;

	case SDL_KEYDOWN:
		ProcessKeyboardEvent(rKEY_DOWN, event);
		break;

	case SDL_KEYUP:
		ProcessKeyboardEvent(rKEY_UP, event);
		break;
	};
}

void rSDLInputManager::ProcessWheelEvent(SDL_Event& event) {
	if (event.wheel.y > 0)
		CreateMouseWheelEvent(rMOUSEWHEEL_UP);
	else if (event.wheel.y < 0)
		CreateMouseWheelEvent(rMOUSEWHEEL_DOWN);
}

void rSDLInputManager::ProcessMouseButtonEvent(rButtonState state, SDL_Event& event){
	rPoint position(event.button.x, event.button.y);

	switch (event.button.button){
	case SDL_BUTTON_LEFT:
		CreateMouseButtonEvent(rMOUSE_BUTTON_LEFT, state, position);
		break;
	case SDL_BUTTON_MIDDLE:
		CreateMouseButtonEvent(rMOUSE_BUTTON_MIDDLE, state, position);
		break;
	case SDL_BUTTON_RIGHT:
		CreateMouseButtonEvent(rMOUSE_BUTTON_RIGHT, state, position);
		break;
	};
}

void rSDLInputManager::ProcessKeyboardEvent(rKeyState state, SDL_Event& event){
	CreateKeyboardEvent(event.key.keysym.sym, state);
}