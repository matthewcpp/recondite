#include "ui/ruiCheckbox.hpp"

ruiCheckbox::ruiCheckbox(int id, const rPoint& position, const rSize& size)
:ruiWidget(id, position, size)
 {
	m_isChecked = false;
 }

void ruiCheckbox::OnTouchDown(const rTouch& touch){
	m_isChecked = !m_isChecked;
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
