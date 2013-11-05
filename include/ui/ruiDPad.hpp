#ifndef RUI_DPAD_HPP
#define RUI_DPAD_HPP

#include <map>

#include "ui/ruiWidget.hpp"
#include "input/rDPad.hpp"
#include "rEngine.hpp"

typedef std::map<int, rDPadButton> rTouchDPadButtonMap;

class ruiDPad : public ruiWidget{
public:
	ruiDPad(rDPad* dpad, int id, const rPoint& position, const rSize& size);

	void SetDPadButtonRect(rDPadButton button, const rRect& rect);
	void CalculateDefaultButtonRects();
	
	virtual void OnTouchDown(const rTouch& touch);
	virtual void OnTouchMove(const rTouch& touch);
	virtual void OnTouchUp(const rTouch& touch);

	virtual void Draw(rEngine& engine);
	
private:

	int TouchCountForButton(rDPadButton button) const;
	void SetButtonStateIfPressed(const rPoint& position, int id);

private:

	rRect m_buttons[4];
	rDPad* m_dpad;
	
	rTouchDPadButtonMap m_touchedButtons;
};

#endif
