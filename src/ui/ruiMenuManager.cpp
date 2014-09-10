#include "ui/ruiMenuManager.hpp"

ruiMenuManager::ruiMenuManager(){
	m_menu = NULL;

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
	if (m_menu)
		delete m_menu;

	m_menu = NULL;
	m_position = rPoint::Zero;
	m_handler = NULL;
}

void ruiMenuManager::Update(rEngine& engine){
}

void ruiMenuManager::Draw(rEngine& engine){
	if (m_menu){
		size_t rowHeight = 30;
		size_t menuItemCount = m_menu->NumItems();
		rColor black(0,0,0,255);
		rColor gray(200,200,200,255);
	
		rFont* font = engine.content->GetFontAsset("consolas");
		rRect bounding(m_position, rSize (100, rowHeight * menuItemCount));
	
		engine.renderer->RenderRect(bounding, gray);
	
		for (size_t i = 0; i < menuItemCount; i++){
			rPoint point(bounding.x, bounding.Top() + (i * rowHeight));
			engine.renderer->RenderString(m_menu->GetItem(i)->Label(), font, point, black);
		}
	}
}

bool ruiMenuManager::OnPointerDown(const rPoint& position){
	if (m_menu){
		CancelContextMenu();
		return true;
	}
	else {
		return false;
	}
}
