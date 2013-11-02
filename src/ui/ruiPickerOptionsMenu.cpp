#include "ui/ruiPickerOptionsMenu.hpp"

ruiPickerOptionsMenu::ruiPickerOptionsMenu(ruiPickerBase* picker, int id)
:ruiWidget(id)
{
	m_picker = picker;
	
	rRect pickerBox = m_picker->BoundingBox();
	
	m_position.Set(pickerBox.x, pickerBox.Bottom() + 20);
	m_size.Set(250, picker->NumOptions() * 30);
}

void ruiPickerOptionsMenu::Update(rEngine& engine){
	rTouch* touch = engine.input->GetTouch(0);

	if (touch && touch->GetType() == rTOUCH_DOWN){
		rPoint touchPos = touch->GetCurrentPosition();
		rRect rect(m_position, m_size);

		if (rect.ContainsPoint(touchPos)){
			int yPos = touchPos.y - m_position.y;
			m_picker->SubmenuSelection( yPos / 30);
		}
	}
}

void ruiPickerOptionsMenu::Draw(rEngine& engine){
	const rArrayString& options = m_picker->Options();
	size_t optionCount = options.size();
	size_t rowHeight = 30;
	rColor black(0,0,0,255);
	rColor gray(200,200,200,255);
	
	rFont* font = engine.content->GetFontAsset("consolas");
	rPoint pickerPos = m_picker->Position();
	
	rRect box(m_position, m_size);
	engine.renderer->RenderRect(box, gray);
	
	for (size_t i =0; i < optionCount; i++){
		rPoint point(box.x, box.Top() + (i * rowHeight));
		engine.renderer->RenderString(options[i], font, point, black);
	}
}