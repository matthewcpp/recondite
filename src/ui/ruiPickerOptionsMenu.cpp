#include "ui/ruiPickerOptionsMenu.hpp"

ruiPickerOptionsMenu::ruiPickerOptionsMenu(ruiIControlWithOptions* picker, ruiIWidgetManager* manager, int id)
:ruiWidget(id)
{
	m_picker = picker;
	m_manager = manager;
}

void ruiPickerOptionsMenu::OnTouchDown(const rTouch& touch){
	rPoint touchPos = touch.GetCurrentPosition();

	int yPos = touchPos.y - m_position.y;
	m_picker->SetSelectionIndex( yPos / 30);

	m_manager->EndModal(this);
}

void ruiPickerOptionsMenu::Draw(rEngine& engine){
	const rArrayString& options = m_picker->Options();
	size_t optionCount = options.size();
	size_t rowHeight = 30;
	rColor black(0,0,0,255);
	rColor gray(200,200,200,255);
	
	rFont* font = engine.content->GetFontAsset("consolas");
	
	rRect box(m_position, m_size);
	engine.renderer->RenderRect(box, gray);
	
	for (size_t i =0; i < optionCount; i++){
		rPoint point(box.x, box.Top() + (i * rowHeight));
		engine.renderer->RenderString(options[i], font, point, black);
	}
}
