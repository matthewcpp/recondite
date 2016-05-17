#include "ui/ruiMenuManager.hpp"

ruiMenuManager::ruiMenuManager(rEngine* engine){
	m_menu = NULL;
	m_engine = engine;

	m_defaultStyle.SetColor("color", rColor(0,0,0,255));
	m_defaultStyle.SetColor("background-color", rColor(200,200,200,255));
	m_defaultStyle.SetString("font", "consolas");

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
	m_menuSize = rSize::Default;
	m_rowHeight = 0;
}

void ruiMenuManager::Update(){}

ruiStyle* ruiMenuManager::GetStyle(){
	if (m_style)
		return m_style;
	else
		return &m_defaultStyle;
}

void ruiMenuManager::CalculateMenuSize(rEngine& engine){
	m_menuSize.Set(0,0);
	if (!m_menu) return;

	ruiStyle* style = GetStyle();
	rString fontName;
	style->GetString("font", fontName);
	//rFont* font = engine.content->Fonts()->Get(fontName);
	
	Font::Face* font = nullptr;
	if (!font) return;

	size_t menuItemCount = m_menu->NumItems();
	//m_rowHeight = font->LineHeight();

	for (size_t i = 0; i < menuItemCount; i++){
		m_menuSize.y += m_rowHeight;
		rSize strSize = font->MeasureString(m_menu->GetItem(i)->Label());
		m_menuSize.x = std::max(m_menuSize.x, strSize.x);
	}
}

void ruiMenuManager::Draw(){
	if (!m_menu) return;

	ruiStyle* style = GetStyle();
	rString fontName;
	style->GetString("font", fontName);
	//rFont* font = engine.content->Fonts()->Get(fontName);
	Font::Face* font = nullptr;
	if (!font) return;

	if (m_menuSize == rSize::Default)
		CalculateMenuSize(*m_engine);

	size_t menuItemCount = m_menu->NumItems();
	rColor color;

	rRect bounding(m_position, m_menuSize);

	style->GetColor("background-color", color);
	m_engine->renderer->SpriteBatch()->RenderRectangle(bounding, color);
	
	style->GetColor("color", color);

	for (size_t i = 0; i < menuItemCount; i++){
		rPoint point(bounding.x, bounding.Top() + (i * m_rowHeight));

		m_engine->renderer->SpriteBatch()->RenderString(m_menu->GetItem(i)->Label(), font, point, color);
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
