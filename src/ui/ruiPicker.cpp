#include "ui/ruiPicker.hpp"

ruiPicker::ruiPicker(int id, const rPoint& position, const rSize& size)
:ruiPickerBase(id,position, size)
{
	m_optionsMenu = NULL;
}

ruiPicker::ruiPicker(rArrayString& options, int id, const rPoint& position, const rSize& size)
:ruiPickerBase(options, id,position, size)
{
}

void ruiPicker::Update(rEngine& engine){
	if (!m_optionsMenu){
		rTouch* touch = engine.input->GetTouch(0);

		if (touch && touch->GetType() == rTOUCH_DOWN){
			rPoint touchPos = touch->GetCurrentPosition();
			rRect rect(m_position, m_size);

			if (rect.ContainsPoint(touchPos)){
				ShowOptionsMenu();
			}
		}
	}
	else{
		m_optionsMenu->Update(engine);
	}
}

void ruiPicker::ShowOptionsMenu(){
	HideOptionsMenu();

	m_optionsMenu = new ruiPickerOptionsMenu(this, -1);
}

void ruiPicker::HideOptionsMenu(){
	if (m_optionsMenu){
		delete m_optionsMenu;
		m_optionsMenu = NULL;
	}
}

void ruiPicker::Draw(rEngine& engine){
	rRect box(m_position, m_size);
	rColor gray(200,200,200,255);
	engine.renderer->RenderRect(box, gray);
	

	rFont* font = engine.content->GetFontAsset("consolas");
	
	if (font){
		rString text = SelectionText();
		rPoint point (m_position.x + 5 , m_position.y + 5);
		rColor black(0,0,0,255);
		
		engine.renderer->RenderString(text,font, point, black);
	}
	
	if (m_optionsMenu){
		m_optionsMenu->Draw(engine);
	}

}

void ruiPicker::SubmenuSelection(size_t index){
	SetSelectionIndex(index);
	HideOptionsMenu();
}
