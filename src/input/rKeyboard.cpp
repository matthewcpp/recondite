#include "input/rKeyboard.hpp"

rKeyState rKeyboard::GetKeyState(rKey key) const {
	if (m_pressedKeys.count(key))
		return rKEY_DOWN;
	else
		return rKEY_UP;
}

void rKeyboard::SetKeyState(rKey key, rKeyState state){
	if (state == rKEY_DOWN)
		m_pressedKeys.insert(key);
	else
		m_pressedKeys.erase(key);
}