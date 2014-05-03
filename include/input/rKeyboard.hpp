#ifndef R_KEYBOARD_HPP
#define R_KEYBOARD_HPP

#include "rBuild.hpp"

typedef int rKey;

enum rKeyState{
	rKEY_UP,
	rKEY_DOWN
};

class RECONDITE_API rKeyboardState{
public:
	virtual rKeyState GetKeyState(rKey key) = 0;
};

class RECONDITE_API rKeyboard : public rKeyboardState{
public:
	virtual rKeyState GetKeyState(rKey key);

	void SetKeyState(rKey key, rKeyState state);

private:
};

#endif