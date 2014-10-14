#include "ui/ruiAnalogStick.hpp"

ruiAnalogStick::ruiAnalogStick(rController* controller, size_t stickIndex, const rString& id, rEngine* engine)
:ruiWidget(id, engine)
{
	m_controller = controller;
	m_stickIndex = stickIndex;
	
	SetCircles();
	
	m_touchId = -1;
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
	
	m_controller->SetAnalogStick(m_stickIndex, x, y);
}

void ruiAnalogStick::OnTouchDown(const rTouch& touch){
	if (m_touchId == -1){
			rVector2 pos = touch.GetCurrentPositionVector();

			if (m_stick.ContainsPoint(pos)){
				m_touchId = touch.Id();
				UpdateController();
			}
	}
}

void ruiAnalogStick::OnTouchMove(const rTouch& touch){
		if (touch.Id() == m_touchId){
			rVector2 pos = touch.GetCurrentPositionVector();

			UpdateStick(pos);
			UpdateController();
		}
}

void ruiAnalogStick::OnTouchUp(const rTouch& touch){
	if (touch.Id() == m_touchId){
		m_stick.center = m_outerCircle.center;
		m_touchId = -1;
		UpdateController();
	}
}

void ruiAnalogStick::Draw(rEngine& engine){
	rColor gray(205,201,201,255);
	rColor darkGray(139,137,137,255);
	
	engine.renderer->RenderCircle(m_outerCircle, gray);
	engine.renderer->RenderCircle(m_stick, darkGray);
}

void ruiAnalogStick::SetCircles(){
	rSize size = Size();
	rRect rect(m_position, size);
	rPoint center = rect.Center();
	
	float rad = ((float)std::max(size.x, size.y) / 2.0f);
	
	m_outerCircle.Set(center.x, center.y, rad);
	m_stick.Set(center.x, center.y, rad / 3.0f);
}

rSize ruiAnalogStick::DoComputeSize() const{
	//temporary implementation;
	return rSize(200,200);
}

rString ruiAnalogStick::GetWidgetType() const{
	return "analogstick";
}