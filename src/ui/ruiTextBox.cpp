#include "ui/ruiTextBox.hpp"

ruiTextBox::ruiTextBox(const rString& id, rEngine* engine)
	:ruiText(id, engine)
{

}

ruiTextBox::ruiTextBox(const rString& text, const rString& id, rEngine* engine)
	:ruiText(text, id, engine)
{

}

void ruiTextBox::OnKeyDown(rKey key, const rKeyboardState& keyboard){
	if (key >= 32 && key <= 176)
		m_text += char(key);

	InvalidateSize();
}
rString ruiTextBox::GetWidgetType() const{
	return "textbox";
}
