#include "ui/ruiTextBox.hpp"

ruiTextBox::ruiTextBox(const rString& id, ruiIDocument* document, rEngine* engine)
	:ruiText(id, document, engine)
{
	Bind(ruiEVT_KEY_DOWN, this, &ruiTextBox::OnKeyDown);
}

ruiTextBox::ruiTextBox(const rString& text, const rString& id, ruiIDocument* document, rEngine* engine)
	: ruiText(text, id, document, engine)
{
	Bind(ruiEVT_KEY_DOWN, this, &ruiTextBox::OnKeyDown);
}

void ruiTextBox::OnKeyDown(rEvent& event){
	ruiKeyEvent& keyEvent = (ruiKeyEvent&)event;
	char key = char(keyEvent.Key());

	if (key == rKEY_BACKSPACE && m_text.length() > 0){
		m_text.pop_back();
	}
	else if (key >= 32 && key <= 176)
		m_text += key;

	InvalidateSize();
}
rString ruiTextBox::GetWidgetType() const{
	return "textbox";
}
