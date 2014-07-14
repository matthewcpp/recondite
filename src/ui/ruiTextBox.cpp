#include "ui/ruiTextBox.hpp"

ruiTextBox::ruiTextBox(const rString& id, ruiIOverlay* overlay, rEngine* engine, const rPoint& position, const rSize& size)
	:ruiText(id, overlay, engine, position, size)
{

}

ruiTextBox::ruiTextBox(const rString& text, const rString& id, ruiIOverlay* overlay, rEngine* engine, const rPoint& position, const rSize& size)
	:ruiText(text, id, overlay, engine, position, size)
{

}

void ruiTextBox::OnKeyDown(rKey key, const rKeyboardState& keyboard){
	if (key >= 32 && key <= 176)
		m_text += char(key);

	m_cachedSize = rSize::Default;
}