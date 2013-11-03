#include "ui/ruiCheckbox.hpp"

ruiCheckbox::ruiCheckbox(int id, const rPoint& position, const rSize& size)
:ruiWidget(id, position, size)
 {
	m_isChecked = false;
 }

bool ruiCheckbox::IsChecked () const{
	return m_isChecked;
}

void ruiCheckbox::SetChecked(bool checked){
	m_isChecked = checked;
}

void ruiCheckbox::Draw(rEngine& engine){
	rRect outline = BoundingBox();
	rColor gray(200,200,200,255);
	
	engine.renderer->RenderWireRect(outline, gray);
	
	if (m_isChecked){
		rColor blue(0,0,255,255);
		rRect fill(outline.x + 5, outline.y + 5, outline.width - 12, outline.height - 12);
		engine.renderer->RenderRect(fill, blue);
	}
}

void ruiCheckbox::Update(rEngine& engine){
	rTouch* touch = engine.input->GetTouch(0);

	if (touch && touch->GetType() == rTOUCH_DOWN){
		rPoint touchPos = touch->GetCurrentPosition();
		rRect box = BoundingBox();

		if (box.ContainsPoint(touchPos)){
			m_isChecked = !m_isChecked;
		}
	}
}