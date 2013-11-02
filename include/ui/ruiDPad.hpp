#ifndef RUI_DPAD_HPP
#define RUI_DPAD_HPP

#include "ui/ruiWidget.hpp"
#include "input/rDPad.hpp"
#include "rEngine.hpp"

class ruiDPad : public ruiWidget{
public:
	ruiDPad(rDPad* dpad, int id, const rPoint& position, const rSize& size);

	void SetDPadButtonRect(rDPadButton button, const rRect& rect);
	void CalculateDefaultButtonRects();
	
	virtual void Update(rEngine& engine);
	virtual void Draw(rEngine& engine);
	
private:

	rRect m_buttons[4];
	
	rDPad* m_dpad;
};

#endif
