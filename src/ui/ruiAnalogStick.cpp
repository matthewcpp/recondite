#include "ui/ruiAnalogStick.hpp"

ruiAnalogStick::ruiAnalogStick(rController* controller, size_t stickIndex, int id, const rPoint& position, const rSize& size)
:ruiWidget(id, position, size)
{
	m_controller = controller;
	m_stickIndex = stickIndex;
	
	SetCircles();
	
	m_touchId = -1;
}

void ruiAnalogStick::UpdateTouchIndicator(rEngine& engine){
	rVector2 touchPos = engine.input->GetTouch(m_touchId)->GetCurrentPositionVector();
	float distance = touchPos.Distance(m_outerCircle.center);
	
	rVector2 pos = touchPos - m_outerCircle.center;
	pos.Normalize();
	
	float radius =  m_outerCircle.radius - m_touchIndicator.radius;
	float scale = distance < radius ? distance : radius;
	pos *= (scale);
	m_touchIndicator.center = m_outerCircle.center + pos;
}

void ruiAnalogStick::UpdateController(){
	float x = rMath::ConvertRange(	m_touchIndicator.center.x, 
									m_outerCircle.center.x - m_outerCircle.radius,
									m_outerCircle.center.x + m_outerCircle.radius,
									-1.0f, 1.0f);
									
	float y = -rMath::ConvertRange(	m_touchIndicator.center.y, 
									m_outerCircle.center.y - m_outerCircle.radius,
									m_outerCircle.center.y + m_outerCircle.radius,
									-1.0f, 1.0f);
	
	m_controller->SetAnalogStick(m_stickIndex, x, y);
}
	
void ruiAnalogStick::Update(rEngine& engine){
	UpdateTouch(engine);
		
	if (m_touchId >= 0){
		UpdateTouchIndicator(engine);
	}
	else{
		m_touchIndicator.center = m_outerCircle.center;
	}
	
	UpdateController();
}

void ruiAnalogStick::Draw(rRenderer* renderer){
	rColor gray(205,201,201,255);
	rColor darkGray(139,137,137,255);
	
	renderer->RenderCircle(m_outerCircle, gray);
	renderer->RenderCircle(m_touchIndicator, darkGray);
}

void ruiAnalogStick::SetCircles(){
	rRect rect(m_position, m_size);
	rPoint center = rect.Center();
	
	float rad = ((float)std::max(m_size.x, m_size.y) / 2.0f);
	
	m_outerCircle.Set(center.x, center.y, rad);
	m_touchIndicator.Set(center.x, center.y, rad / 3.0f);
}

int ruiAnalogStick::UpdateTouch(rEngine& engine){
	if (m_touchId  >= 0){
		if (engine.input->GetTouch(m_touchId) == NULL)
			m_touchId = -1;
	}
	else{
		rTouchArray touches;
		engine.input->GetTouches(touches);
		
		for (size_t i = 0; i < touches.size(); i++){
			if (touches[i]->GetType() == rTOUCH_DOWN){
				rVector2 pt = touches[i]->GetCurrentPositionVector();
				
				if (m_touchIndicator.ContainsPoint(pt)){
					m_touchId = touches[i]->Id();
					break;
				}
			}
		}
	}
	
	return 0;
}
