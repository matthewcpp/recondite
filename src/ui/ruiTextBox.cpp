#include "ui/ruiTextBox.hpp"

ruiTextBox::ruiTextBox(const rString& id, ruiIDocument* document, rEngine* engine)
	:ruiText(id, document, engine)
{

}

ruiTextBox::ruiTextBox(const rString& text, const rString& id, ruiIDocument* document, rEngine* engine)
	: ruiText(text, id, document, engine)
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
