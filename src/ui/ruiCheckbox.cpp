#include "ui/ruiCheckbox.hpp"

ruiCheckbox::ruiCheckbox(const rString& id, ruiIOverlay* overlay, rEngine* engine, const rPoint& position, const rSize& size)
:ruiWidget(id, overlay, engine, position, size)
 {
	m_isChecked = false;
 }

void ruiCheckbox::OnPointerDown(const rPoint& position){
	SetChecked( !m_isChecked);
}

bool ruiCheckbox::IsChecked () const{
	return m_isChecked;
}

void ruiCheckbox::SetChecked(bool checked){
	if (checked != m_isChecked){
		m_isChecked = checked;
		Trigger(ruiEVENT_CHECKBOX_CHANGE);
	}
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
