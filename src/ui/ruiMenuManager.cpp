#include "ui/ruiMenuManager.hpp"

ruiMenuManager::ruiMenuManager(rEngine* engine){
	m_menu = NULL;
	m_engine = engine;

	CancelContextMenu();
}

bool ruiMenuManager::ShowContextMenu(rViewport* viewport, ruiMenu* menu, ruiStyle* style, const rPoint& position, rEventHandler* handler){
	if (m_menu){
		return false;
	}
	else{
		m_menu = menu;
		m_position = position;
		m_handler = handler;
		m_style = style;
		m_viewport = viewport;

		CalculateMenuSize();

		return true;
	}
}

void ruiMenuManager::CancelContextMenu(){
	m_menu = NULL;
	m_position = rPoint::Zero;
	m_handler = NULL;
	m_style = NULL;
	m_menuSize = rSize::Default;
	m_rowHeight = 0;
	m_viewport = nullptr;
}

void ruiMenuManager::Update(){}

void ruiMenuManager::CalculateMenuSize(){
	m_menuSize.Set(0,0);
	if (!m_menu) return;
	
	Font::Face* font = m_engine->content->Fonts()->SystemDefault();
	m_rowHeight = font->GetLineHeight();

	size_t menuItemCount = m_menu->NumItems();

	for (size_t i = 0; i < menuItemCount; i++){
		rSize strSize = font->MeasureString(m_menu->GetItem(i)->Label());

		m_menuSize.x = std::max(m_menuSize.x, strSize.x);
		m_menuSize.y += font->GetLineHeight();
	}

	AdjustMenuPosition();
}

void ruiMenuManager::AdjustMenuPosition() {
	rRect screenRect = m_viewport->GetScreenRect();

	int menuBottom = m_position.y + m_menuSize.y;
	int screenBottom = screenRect.Bottom();

	if (menuBottom > screenBottom) {
		m_position.y -= menuBottom - screenBottom;
	}
}

void ruiMenuManager::Draw(){
	if (!m_menu) return;

	Font::Face* font = m_engine->content->Fonts()->SystemDefault();
	if (!font) return;

	size_t menuItemCount = m_menu->NumItems();
	rColor color = rColor::White;

	rRect bounding(m_position, m_menuSize);

	m_style->GetColor("background-color", color);
	m_engine->renderer->SpriteBatch()->RenderRectangle(bounding, color, 0.9);
	
	color = rColor::Black;
	m_style->GetColor("color", color);

	for (size_t i = 0; i < menuItemCount; i++){
		rPoint point(bounding.x, bounding.Top() + (i * m_rowHeight));

		m_engine->renderer->SpriteBatch()->RenderString(m_menu->GetItem(i)->Label(), font, point, color, 0.91);
	}
}

bool ruiMenuManager::PickMenuItem(const rPoint& position){
	if (m_handler){
		rRect boundingBox(m_position, m_menuSize);

		if (boundingBox.ContainsPoint(position)){
			int item = (position.y - boundingBox.y) / m_rowHeight;
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
