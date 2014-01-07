#ifndef R_MOUSE_HPP
#define R_MOUSE_HPP

#include "rPoint.hpp"
#include "input/rInputButton.hpp"

enum rMouseButton{
	rMOUSE_BUTTON_LEFT = 0,
	rMOUSE_BUTTON_MIDDLE,
	rMOUSE_BUTTON_RIGHT
};

class rMouseState {
public:
	virtual rPoint Position() const = 0;
	virtual rPoint PreviousPosition() const = 0;

	virtual rButtonState GetButtonState(rMouseButton button) const = 0;
};

class rMouse : public rMouseState{
public:
	rMouse();

	void SetPosition(const rPoint& position);
	void SetPosition(int x, int y);
	virtual rPoint Position() const;
	virtual rPoint PreviousPosition() const;

	virtual rButtonState GetButtonState(rMouseButton button) const;
	void SetButtonState (rMouseButton button, rButtonState state);

private:
	rPoint m_position;
	rPoint m_previousPosition;
	rInputButton m_buttons[3];
};

#endif