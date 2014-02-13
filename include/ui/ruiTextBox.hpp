#ifndef RUI_TEXTBOX_HPP
#define RUI_TEXTBOX_HPP

#include "ui/ruiText.hpp"

class ruiTextBox : public ruiText{
public:
	
	ruiTextBox(int id, const rPoint& position, const rSize& size);
	ruiTextBox(const rString& text, int id, const rPoint& position, const rSize& size);

public:
	virtual void OnKeyDown(rKey key, const rKeyboardState& keyboard);

private:

};

#endif