#include "ui/ruiSlider.hpp"

ruiSlider::ruiSlider(const rString& id, rEngine* engine, const rPoint& position, const rSize& size)
:ruiWidget(id, engine, position, size)
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
	rLog::Trace("start drag");
	m_prevDrag = position;
	handleGrabbed = true;
}

void ruiSlider::HandleDrag(const rPoint& position){
	rPoint delta = position - m_prevDrag;
	int change = int(rMath::RoundToInt(((float)delta.x / (float)m_size.x) * 100.0f));
	
	SetValue(rMath::Clamp(m_value + change, 0 , 100));
	
	m_prevDrag = position;
}

rRect ruiSlider::HandleRect() const{
	float ratio =  m_value / 100.0f;
	int handleOffset = int (m_size.x * ratio) - (m_handleSize / 2);
	
	return rRect(m_position.x + handleOffset, m_position.y - 3, m_handleSize, m_size.y + 6);
}

void ruiSlider::Draw(rEngine& engine){
	rRect box = BoundingBox();
	rRect handle = HandleRect();
	
	rColor gray(200,200,200,255);
	rColor white(255,255,255,255);
	
	engine.renderer->RenderRect(box, gray);
	engine.renderer->RenderRect(handle, white);
}

rString ruiSlider::GetWidgetType() const{
	return "slider";
}