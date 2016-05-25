#ifndef R_KEYBOARD_HPP
#define R_KEYBOARD_HPP

#include <set>

#include "rBuild.hpp"

typedef int rKey;

enum rKeyState{
	rKEY_UP,
	rKEY_DOWN
};

enum rKeyCode{
	rKEY_BACKSPACE = 8
};

class RECONDITE_API rKeyboardState{
public:
	virtual rKeyState GetKeyState(rKey key) const = 0;
};

class RECONDITE_API rKeyboard : public rKeyboardState{
public:
	virtual rKeyState GetKeyState(rKey key) const;

	void SetKeyState(rKey key, rKeyState state);

private:
	typedef std::set<rKey> rKeySet;

private:
	rKeySet m_pressedKeys;
};

#endif