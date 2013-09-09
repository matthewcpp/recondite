#include "input/rController.hpp"

rController::rController(unsigned int buttonCount, unsigned int dPadCount, unsigned int analogStickCount, unsigned int triggerCount){
	Init(buttonCount, dPadCount, analogStickCount, triggerCount);
}

void rController::Init(unsigned int buttonCount, unsigned int dPadCount, unsigned int analogStickCount, unsigned int triggerCount){
	m_buttons.resize(buttonCount);
	m_dPads.resize(dPadCount);
	
	if (analogStickCount){
		m_analogSticks.resize(analogStickCount);
		memset(&m_analogSticks[0], sizeof (rVector2Array::value_type) * analogStickCount, 0);
	}
	
	if (triggerCount){
		m_triggers.resize(triggerCount);
		memset(&m_triggers[0], sizeof (rFloatArray::value_type) * triggerCount, 0);
	}
}

unsigned int rController::ButtonCount() const{
	return m_buttons.size();
}

unsigned int rController::DPadCount() const{
	return m_dPads.size();
}

unsigned int rController::AnalogStickCount() const{
	return m_analogSticks.size();
}

unsigned int rController::TriggerCount() const{
	return m_triggers.size();
}

const rControllerButton* rController::Button(unsigned int index) const{
	if (index >= m_buttons.size())
		return NULL;
	else
		return &m_buttons[index];
}

const rDPad* rController::DPad(unsigned int index) const{
	if (index >= m_dPads.size())
		return NULL;
	else
		return &m_dPads[index];
}

const rVector2* rController::AnalogStick(unsigned int index) const{
	if (index >= m_analogSticks.size())
		return NULL;
	else
		return &m_analogSticks[index];
}

float rController::Trigger(unsigned int index) const{
	if (index >= m_buttons.size())
		return 0.0f;
	else
		return m_triggers[index];
}

bool rController::SetButton(unsigned int index, rButtonState state){
	if (index < m_buttons.size()){
		m_buttons[index].SetButtonState(state);
		return true;
	}
	else{
		return false;
	}
}

bool rController::SetDPadButton(unsigned int index, rDPadButton button, rButtonState state){
	if (index < m_dPads.size()){
		m_dPads[index].SetButtonState(button, state);
		return true;
	}
	else{
		return false;
	}
}

bool rController::SetAnalogStick(unsigned int index, float x, float y){
	if (index < m_analogSticks.size()){
		m_analogSticks[index].Set(x,y);
		return true;
	}
	else{
		return false;
	}
}

bool rController::SetTrigger(unsigned int index, float value){
	if (index < m_triggers.size()){
		m_triggers[index] = value;
		return true;
	}
	else{
		return false;
	}
}
