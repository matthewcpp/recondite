#include "ui/ruiMenuManager.hpp"

ruiMenuManager::ruiMenuManager(){
	CancelContextMenu();
}

bool ruiMenuManager::ShowContextMenu(const ruiMenu* menu, const rPoint& position, rEventHandler* handler){
	if (m_menu){
		return false;
	}
	else{
		m_menu = menu;
		m_position = position;
		m_handler = handler;
		return true;
	}
}

void ruiMenuManager::CancelContextMenu(){
	m_menu = NULL;
	m_position = rPoint::Zero;
	m_handler = NULL;
}

void ruiMenuManager::Update(rEngine& engine){
}

void ruiMenuManager::Draw(rEngine& engine){

}
