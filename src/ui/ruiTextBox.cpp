#include "ui/ruiTextBox.hpp"

ruiTextBox::ruiTextBox(int id, const rPoint& position, const rSize& size)
	:ruiText(id, position, size)
{

}

ruiTextBox::ruiTextBox(const rString& text, int id, const rPoint& position, const rSize& size)
	:ruiText(text, id, position, size)
{

}

void ruiTextBox::OnKeyDown(rKey key, const rKeyboardState& keyboard){
	if (key >= 32 && key <= 176)
		m_text += char(key);
}