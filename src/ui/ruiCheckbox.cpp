#include "ui/ruiCheckbox.hpp"

ruiCheckbox::ruiCheckbox(const rString& id, ruiIDocument* document, rEngine* engine)
	:ruiWidget(id, document, engine)
 {
	m_isChecked = false;
 }

bool ruiCheckbox::IsChecked () const{
	return m_isChecked;
}

void ruiCheckbox::SetChecked(bool checked){
	if (checked != m_isChecked){
		m_isChecked = checked;
		ruiWidgetEvent event(this);
		Trigger(ruiEVENT_CHECKBOX_CHANGE, event);
	}
}

void ruiCheckbox::Draw(){
	ruiStyle* style = ComputedStyle();
	rRect outline = BoundingBox();

	rColor color(200,200,200,255);
	style->GetColor("border-color", color);

	m_engine->renderer->SpriteBatch()->RenderWireRectangle(outline, color, 0.01);
	
	if (m_isChecked){
		color.Set(0,0,255,255);
		style->GetColor("color", color);

		m_engine->renderer->SpriteBatch()->RenderRectangle(outline, color);
	}
}

bool ruiCheckbox::OnPointerUp(const rPoint& position){
	rRect boundingBox = BoundingBox();

	if (boundingBox.ContainsPoint(position)){
		SetChecked( !m_isChecked);
		return true;
	}
	else{
		return false;
	}
}

bool ruiCheckbox::OnPointerDown(const rPoint& position) {
	return true;
}

rSize ruiCheckbox::ComputeSize(){
	//temporary
	return rSize(15,15);
}

rString ruiCheckbox::GetWidgetType() const{
	return "checkbox";
}