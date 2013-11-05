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

void ruiDPad::Draw(rEngine& engine){
	
	rColor gray(205,201,201,255);
	rColor darkGray(139,137,137,255);
	
	for (int button = rDPAD_LEFT; button <= rDPAD_DOWN; button++){
			if (m_dpad->GetButton((rDPadButton)button).Down()){
				engine.renderer->RenderRect(m_buttons[button], darkGray);
			}
			else{
				engine.renderer->RenderRect(m_buttons[button], gray);
			}
	}
}

void ruiDPad::SetButtonStateIfPressed(const rPoint& position, int id){
	for (int button = rDPAD_LEFT; button <= rDPAD_DOWN; button++){
		if (m_buttons[button].ContainsPoint(position)){
			m_dpad->SetButtonState((rDPadButton)button, rBUTTON_STATE_DOWN);
			m_touchedButtons[id] = (rDPadButton)button;
		}
	}
}

void ruiDPad::OnTouchDown(const rTouch& touch){
	rPoint position = touch.GetCurrentPosition();
	SetButtonStateIfPressed(position, touch.Id());
}

void ruiDPad::OnTouchMove(const rTouch& touch){
	rPoint position = touch.GetCurrentPosition();
	int touchId = touch.Id();
	
	if (m_touchedButtons.count(touchId)){
		rDPadButton button = m_touchedButtons[touchId];
		
		if (m_buttons[button].ContainsPoint(position)){
			m_dpad->SetButtonState(button, rBUTTON_STATE_DOWN);
		}
		else{
			if (TouchCountForButton(button) == 1){
				m_dpad->SetButtonState(button, rBUTTON_STATE_UP);
			}

			m_touchedButtons.erase(touchId);
		}
	}
	else{
		SetButtonStateIfPressed(position, touchId);
	}
}

void ruiDPad::OnTouchUp(const rTouch& touch){
	int touchId = touch.Id();
	
	if (m_touchedButtons.count(touchId)){
		rDPadButton button = m_touchedButtons[touchId];

		if (TouchCountForButton(button) == 1){
			m_dpad->SetButtonState(button, rBUTTON_STATE_UP);
		}

		m_touchedButtons.erase(touchId);
	}
}

int ruiDPad::TouchCountForButton(rDPadButton button) const{
	rTouchDPadButtonMap::const_iterator end = m_touchedButtons.end();

	int count = 0;

	for (rTouchDPadButtonMap::const_iterator it = m_touchedButtons.begin(); it != end; ++it){
		if (it->second == button)
			count += 1;
	}

	return count;
}

