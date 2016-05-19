#include "ui/ruiCheckbox.hpp"

ruiCheckbox::ruiCheckbox(const rString& id, ruiDocument* document, rEngine* engine)
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

	m_engine->renderer->SpriteBatch()->RenderWireRectangle(outline, color);
	
	if (m_isChecked){
		color.Set(0,0,255,255);
		style->GetColor("color", color);

		rRect fill(outline.x + 5, outline.y + 5, outline.width - 12, outline.height - 12);
		m_engine->renderer->SpriteBatch()->RenderRectangle(fill, color);
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

rSize ruiCheckbox::ComputeSize(){
	//temporary
	return rSize(35,35);
}

rString ruiCheckbox::GetWidgetType() const{
	return "checkbox";
}