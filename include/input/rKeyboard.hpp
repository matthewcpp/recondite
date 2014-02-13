#ifndef R_KEYBOARD_HPP
#define R_KEYBOARD_HPP

typedef int rKey;

enum rKeyState{
	rKEY_UP,
	rKEY_DOWN
};

class rKeyboardState{
public:
	virtual rKeyState GetKeyState(rKey key) = 0;
};

class rKeyboard : public rKeyboardState{
public:
	virtual rKeyState GetKeyState(rKey key);

	void SetKeyState(rKey key, rKeyState state);

private:
};

#endif