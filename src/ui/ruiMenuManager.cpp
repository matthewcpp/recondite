#include "ui/ruiMenuManager.hpp"

ruiMenuManager::ruiMenuManager(){
	m_menu = NULL;

	m_defaultStyle.SetColor("color", rColor(0,0,0,255));
	m_defaultStyle.SetColor("background-color", rColor(200,200,200,255));

	CancelContextMenu();
}

bool ruiMenuManager::ShowContextMenu(ruiMenu* menu, ruiStyle* style, const rPoint& position, rEventHandler* handler){
	if (m_menu){
		return false;
	}
	else{
		m_menu = menu;
		m_position = position;
		m_handler = handler;
		m_style = style;
		return true;
	}
}

void ruiMenuManager::CancelContextMenu(){
	if (m_menu)
		delete m_menu;

	m_menu = NULL;
	m_position = rPoint::Zero;
	m_handler = NULL;
	m_style = NULL;
}

void ruiMenuManager::Update(rEngine& engine){
}

ruiStyle* ruiMenuManager::GetStyle(){
	if (m_style)
		return m_style;
	else
		return &m_defaultStyle;
}

void ruiMenuManager::Draw(rEngine& engine){
	if (!m_menu)
		return;

	ruiStyle* style = GetStyle();
	size_t rowHeight = 30;
	size_t menuItemCount = m_menu->NumItems();
	rColor color;

	style->GetColor("background-color", color);
	rRect bounding(m_position, rSize (100, rowHeight * menuItemCount));
	engine.renderer->RenderRect(bounding, color);
	
	style->GetColor("color", color);
	rFont* font = engine.content->GetFontAsset("consolas");
	for (size_t i = 0; i < menuItemCount; i++){
		rPoint point(bounding.x, bounding.Top() + (i * rowHeight));
		engine.renderer->RenderString(m_menu->GetItem(i)->Label(), font, point, color);
	}
}

bool ruiMenuManager::PickMenuItem(const rPoint& position){
	if (m_handler){
		rRect boundingBox(m_position, rSize(100, 30 * m_menu->NumItems()));

		if (boundingBox.ContainsPoint(position)){
			int item = (position.y - boundingBox.y) / 30;
			ruiMenuItem* menuItem = m_menu->GetItem(item);
			ruiMenuEvent event(m_menu, menuItem->Id());

			m_handler->Trigger(ruiEVT_MENU,event);

			return true;
		}
	}

	return false;
}

bool ruiMenuManager::OnPointerDown(const rPoint& position){
	if (m_menu){
		PickMenuItem(position);
		CancelContextMenu();
		return true;
	}
	else {
		return false;
	}
}
