#include "rInputManager.hpp"

rInputManager::rInputManager(){
	m_ui = NULL;
}

void rInputManager::SetUI(ruiInput* uiInput){
	m_ui = uiInput;
}

size_t rInputManager::TouchCount() const{
	return m_touches.size();
}

rTouch* rInputManager::CreateTouch(int id, const rPoint& position, rTouchType type){
	if (m_touches.count(id)){
		return NULL;
	}
	else{
		rTouch* touch = new rTouch(id, position, type);
		m_touches[id] = touch;

		rLog::Info("Touch (%u) created Pos: %d, %d (%u)", id, position.x, position.y, type);

		m_gestures.OnTouchDown(*touch);
		m_ui->InjectTouchDown(*touch);

		return touch;
	}
}

rTouch* rInputManager::GetTouch(int id){
	rTouchMap::iterator t = m_touches.find(id);
	
	if (t == m_touches.end())
		return NULL;
	else
		return t->second;
}

bool rInputManager::UpdateTouch(int id, const rPoint& position, rTouchType type){
	rTouch* touch = GetTouch(id);
	
	if (touch){
		touch->Update(position, type);
		
		if (type == rTOUCH_UP){
			m_gestures.OnTouchUp(*touch);
			m_ui->InjectTouchUp(*touch);

			m_touches.erase(id);
			delete touch;

			rLog::Info("Touch (%u) deleted Pos: %d, %d (%u)", id, position.x, position.y, type);
		}
		else{
			//rLog::Trace("Touch (%u) updated Pos: %d, %d (%u)", id, position.x, position.y, type);
			m_gestures.OnTouchMove(*touch);
			m_ui->InjectTouchMove(*touch);
		}
		
		return true;
	}
	else{
		return false;
	}
}

void rInputManager::GetTouchIds(rIntArray& ids){
	ids.clear();

	for (rTouchMap::iterator it = m_touches.begin(); it != m_touches.end(); ++it)
		ids.push_back(it->first);
}

rController* rInputManager::CreateController(unsigned int buttonCount, unsigned int dPadCount, unsigned int analogStickCount, unsigned int triggerCount){
	rController* controller = new rController(buttonCount, dPadCount, analogStickCount, triggerCount);
	m_controllers.push_back(controller);
	
	return controller;
}

size_t rInputManager::ControllerCount() const{
	return m_controllers.size();
}

rControllerState* rInputManager::GetControllerState(size_t index) const{
	return GetController(index);
}

rController* rInputManager::GetController(size_t index) const{
	if (index >= m_controllers.size())
		return NULL;
	else
		return m_controllers[index];
}

void rInputManager::CreateKeyboardEvent(rKey key, rKeyState state){
	m_keyboard.SetKeyState(key, state);

	if (state == rKEY_DOWN)
		m_ui->InjectKeyDownEvent(key, m_keyboard);
	else
		m_ui->InjectKeyUpEvent(key, m_keyboard);
}

const rKeyboardState* rInputManager::GetKeyboardState() const{
	return &m_keyboard;
}

void rInputManager::CreateMouseMotionEvent(int x, int y){
	m_mouse.SetPosition(x,y);
	m_ui->InjectMouseMotionEvent(m_mouse);
}

void rInputManager::CreateMouseButtonEvent(rMouseButton button, rButtonState state, const rPoint& position){
	m_mouse.SetPosition(position);
	m_mouse.SetButtonState(button, state);

	if (state == rBUTTON_STATE_DOWN){
		m_ui->InjectMouseDownEvent(button, m_mouse);
	}
	else{
		m_ui->InjectMouseUpEvent(button, m_mouse);
	}
}

void rInputManager::CreateMouseWheelEvent(rMouseWheelDirection direction){
	m_mouse.UpdateWheelValue(direction);

	m_ui->InjectMouseWheelEvent(direction, m_mouse);
}

const rMouseState* rInputManager::GetMouseState() const{
	return &m_mouse;
}

const riGestureTracker* rInputManager::Gestures() const{
	return &m_gestures;
}
