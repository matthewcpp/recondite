#include "rInputManager.hpp"

rTouch* rInputManager::CreateTouch(unsigned int id, const rPoint& position, rTouchType type){
	if (m_touches.count(id)){
		return NULL;
	}
	else{
		rTouch* touch = new rTouch(id, position, type);
		m_touches[id] = touch;
		rLog::Info("Touch (%u) created Pos: %d, %d (%u)", id, position.x, position.y, type);
		return touch;
	}
}

rTouch* rInputManager::GetTouch(unsigned int id){
	rTouchMap::iterator t = m_touches.find(id);
	
	if (t == m_touches.end())
		return NULL;
	else
		return t->second;
}

bool rInputManager::UpdateTouch(unsigned int id, const rPoint& position, rTouchType type){
	rTouch* touch = GetTouch(id);
	
	if (touch){
		touch->Update(position, type);
		
		if (type == rTOUCH_UP){
			m_touches.erase(id);
			delete touch;

			rLog::Info("Touch (%u) deleted Pos: %d, %d (%u)", id, position.x, position.y, type);
		}
		else{
			rLog::Trace("Touch (%u) updated Pos: %d, %d (%u)", id, position.x, position.y, type);
		}
		
		return true;
	}
	else{
		return false;
	}
}

void rInputManager::GetTouches(rTouchArray& touches){
	touches.clear();
	
	for (rTouchMap::const_iterator it = m_touches.begin(); it != m_touches.end(); ++it)
		touches.push_back(it->second);
}

size_t rInputManager::TouchCount() const{
	return m_touches.size();
}

void rInputManager::GetTouchIds(rIntArray& ids){
	ids.clear();

	for (rTouchMap::iterator it = m_touches.begin(); it != m_touches.end(); ++it)
		ids.push_back(it->first);
}

rController* rInputManager::CreateController(unsigned int buttonCount, unsigned int dPadCount, unsigned int analogStickCount, unsigned int triggerCount){
	rController* controller = new Controller(buttonCount, dPadCount, analogStickCount, triggerCount);
	m_controllers.push_back(controller);
	
	return controller;
}

size_t rInputManager::ControllerCount() const(){
	return m_controllers.size();
}

rControllerState* rInputManager::GetControllerState(size_t index) const{
	return GetController(index);
}

rController* rInputManager::GetController(size_t index) const{
	if (index >= m_controllers.size())
		return NULL;
	else
		return m_controllers[i];
}
