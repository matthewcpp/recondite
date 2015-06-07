#include "ui/ruiSlider.hpp"

ruiSlider::ruiSlider(const rString& id, rEngine* engine)
:ruiWidget(id, engine)
{
	m_value = 0;
	m_handleSize = 15;
	
	handleGrabbed = false;
}

int ruiSlider::GetValue() const{
	return m_value;
}

void ruiSlider::SetValue(int value){
	value = rMath::Clamp<int>(value, 0 , 100);

	if (value != m_value){
		m_value = rMath::Clamp<int>(value, 0 , 100);
		//Trigger(ruiEVENT_SLIDER_CHANGE);
	}
}

void ruiSlider::SetHandleSize(int size){
	m_handleSize = size;
}

int ruiSlider::GetHandleSize() const{
	return m_handleSize;
}

bool ruiSlider::OnPointerDown(const rPoint& position){
	rRect handle = HandleRect();

	if (handle.ContainsPoint(position)){
		StartDrag(position);
		return true;
	}
	else{
		handleGrabbed = false;
		return false;
	}
}

bool ruiSlider::OnPointerUp(const rPoint& position){
	if (handleGrabbed){
		handleGrabbed = false;
		return true;
	}
	else{
		return false;
	}
}

bool ruiSlider::OnPointerMove(const rPoint& position){
	if (handleGrabbed){
		HandleDrag(position);
		return true;
	}
	else{
		return false;
	}
}

void ruiSlider::StartDrag(const rPoint& position){
	m_prevDrag = position;
	handleGrabbed = true;
}

void ruiSlider::HandleDrag(const rPoint& position){
	rSize size = Size();
	rPoint delta = position - m_prevDrag;
	int change = int(rMath::RoundToInt(((float)delta.x / (float)size.x) * 100.0f));
	
	SetValue(rMath::Clamp(m_value + change, 0 , 100));
	
	m_prevDrag = position;
}

rRect ruiSlider::HandleRect(){
	rSize size = Size();
	float ratio =  m_value / 100.0f;
	int handleOffset = int (size.x * ratio) - (m_handleSize / 2);
	
	return rRect(m_position.x + handleOffset, m_position.y - 3, m_handleSize, size.y + 6);
}

rSize ruiSlider::ComputeSize(){
	//temporary
	return rSize(130,35);
}

void ruiSlider::Draw(){
	rRect box = BoundingBox();
	rRect handle = HandleRect();
	ruiStyle* style = ComputedStyle();
	
	rColor color(200,200,200,255);
	style->GetColor("background-color", color);
	m_engine->renderer->RenderRect(box, color);

	color.Set(255,255,255,255);
	style->GetColor("color", color);
	m_engine->renderer->RenderRect(handle, color);
}

rString ruiSlider::GetWidgetType() const{
	return "slider";
}