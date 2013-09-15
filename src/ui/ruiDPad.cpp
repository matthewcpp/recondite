#include "ui/ruiDPad.hpp"
#include "rLog.hpp"

ruiDPad::ruiDPad(rDPad* dpad, int id, const rPoint& position, const rSize& size)
:ruiWidget(id, position, size)
{
	CalculateDefaultButtonRects();
	
	m_dpad = dpad;
}

void ruiDPad::SetDPadButtonRect(rDPadButton button, const rRect& rect){
	m_buttons[button] = rect;
}

void ruiDPad::CalculateDefaultButtonRects(){
	rSize squareSize (m_size.x / 3 , m_size.y / 3);
	
	m_buttons[rDPAD_UP].Set(m_position.x + squareSize.x, m_position.y, squareSize.x, squareSize.y);
	m_buttons[rDPAD_LEFT].Set(m_position.x, m_position.y + squareSize.y, squareSize.x, squareSize.y);
	m_buttons[rDPAD_RIGHT].Set(m_position.x + (2 * squareSize.x), m_position.y + squareSize.y, squareSize.x, squareSize.y);
	m_buttons[rDPAD_DOWN].Set(m_position.x + squareSize.x, m_position.y + (2 * squareSize.y), squareSize.x, squareSize.y);
}

void ruiDPad::Draw(rRenderer* renderer){
	
	rColor gray(205,201,201,255);
	rColor darkGray(139,137,137,255);
	
	for (int button = rDPAD_LEFT; button <= rDPAD_DOWN; button++){
			if (m_dpad->GetButton((rDPadButton)button).Down()){
				renderer->RenderRect(m_buttons[button], darkGray);
			}
			else{
				renderer->RenderRect(m_buttons[button], gray);
			}
	}
}

void ruiDPad::Update(rEngine& engine){
	rTouchArray touches;
	engine.input->GetTouches(touches);
	
	rButtonState states[] = {rBUTTON_STATE_UP, rBUTTON_STATE_UP, rBUTTON_STATE_UP, rBUTTON_STATE_UP};
	
	for (size_t i = 0; i < touches.size(); i++){
		rPoint position = touches[i]->GetCurrentPosition();
		
		for (int button = rDPAD_LEFT; button <= rDPAD_DOWN; button++){
			if (m_buttons[button].ContainsPoint(position))
				states[button] = rBUTTON_STATE_DOWN;
		}
	}
	
	
	for (int button = rDPAD_LEFT; button <= rDPAD_DOWN; button++){
			m_dpad->SetButtonState((rDPadButton)button, states[button]);
	}
}