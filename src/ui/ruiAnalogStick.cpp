#include "ui/ruiAnalogStick.hpp"

ruiAnalogStick::ruiAnalogStick(const rString& id, ruiIDocument* document, rEngine* engine)
	:ruiWidget(id, document, engine)
{
	m_controller = nullptr;
	m_stickIndex = 0;
	
	float radius = 100.0f;
	m_outerCircle.Set(0.0f, 0.0f, radius);
	m_stick.Set(0.0f, 0.0f, radius / 3.0f);
	
	m_dragging = false;
}

void ruiAnalogStick::SetController(rController* controller, size_t stickIndex){
	m_controller = controller;
	m_stickIndex = stickIndex;
}

void ruiAnalogStick::SetPosition(int x, int y){
	ruiWidget::SetPosition(x, y);

	m_outerCircle.center.Set(x + m_outerCircle.radius, y + m_outerCircle.radius);
	m_stick.center = m_outerCircle.center;

}
void ruiAnalogStick::SetPosition(const rPoint& position){
	ruiWidget::SetPosition(position);

	m_outerCircle.center.Set(position.x + m_outerCircle.radius, position.y + m_outerCircle.radius);
	m_stick.center = m_outerCircle.center;
}

void ruiAnalogStick::UpdateStick(const rVector2& position){
	float distance = position.Distance(m_outerCircle.center);

	rVector2 pos = position - m_outerCircle.center;
	pos.Normalize();

	float radius =  m_outerCircle.radius - m_stick.radius;
	float scale = distance < radius ? distance : radius;
	pos *= (scale);
	m_stick.center = m_outerCircle.center + pos;
}

void ruiAnalogStick::UpdateController(){
	float x = rMath::ConvertRange(	m_stick.center.x,
									m_outerCircle.center.x - m_outerCircle.radius,
									m_outerCircle.center.x + m_outerCircle.radius,
									-1.0f, 1.0f);
									
	float y = -rMath::ConvertRange(	m_stick.center.y,
									m_outerCircle.center.y - m_outerCircle.radius,
									m_outerCircle.center.y + m_outerCircle.radius,
									-1.0f, 1.0f);
	
	if (m_controller) m_controller->SetAnalogStick(m_stickIndex, x, y);
}

bool ruiAnalogStick::OnPointerDown(const rPoint& position){
	rVector2 pos((float)position.x, (float)position.y);

	if (m_stick.ContainsPoint(pos)){
		UpdateController();
		m_dragging = true;
		return true;
	}
	else{
		return false;
	}
}

bool ruiAnalogStick::OnPointerMove(const rPoint& position){
	rVector2 pos((float)position.x, (float)position.y);

	if (m_dragging){
		UpdateStick(pos);
		UpdateController();
		return true;
	}
	else{
		return false;
	}
}

bool ruiAnalogStick::OnPointerUp(const rPoint& position){
	if (m_dragging){
		m_stick.center = m_outerCircle.center;
		m_dragging = false;
		UpdateController();
		return true;
	}
	else{
		return false;
	}
}

void ruiAnalogStick::Draw(){
	rColor gray(205,201,201,255);
	rColor darkGray(139,137,137,255);
	
	m_engine->renderer->SpriteBatch()->RenderCircle(m_outerCircle, gray, 0.0f);
	m_engine->renderer->SpriteBatch()->RenderCircle(m_stick, darkGray, 0.01f);
}

rSize ruiAnalogStick::ComputeSize() {
	//temporary implementation;
	return rSize(200,200);
}

rString ruiAnalogStick::GetWidgetType() const{
	return "analogstick";
}