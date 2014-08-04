#include "ui/ruiMenu.hpp"

ruiMenu::ruiMenu(){
}

ruiMenu::~ruiMenu(){
	Clear();
}

ruiMenuItem* ruiMenu::AppendItem(int id, const rString& label){
	ruiMenuItem* item = new ruiMenuItem(id, label);
	m_menuItems.push_back(item);

	return item;
}

void ruiMenu::Clear(){
	for (size_t i = 0; i < m_menuItems.size(); i++)
		delete m_menuItems[i];

	m_menuItems.clear();
}

ruiMenuItem* ruiMenu::GetItem(size_t index) const{
	if (index >= m_menuItems.size())
		return NULL;
	else
		return m_menuItems[index];
}

void ruiMenu::DeleteItem(size_t index){
	if (index < m_menuItems.size())
		m_menuItems.erase(m_menuItems.begin() + index);
}

void ruiMenu::Draw(const rRect& bounding, rEngine& engine){
	size_t rowHeight = 30;
	rColor black(0,0,0,255);
	rColor gray(200,200,200,255);
	
	rFont* font = engine.content->GetFontAsset("consolas");
	
	engine.renderer->RenderRect(bounding, gray);
	
	for (size_t i =0; i < m_menuItems.size(); i++){
		rPoint point(bounding.x, bounding.Top() + (i * rowHeight));
		engine.renderer->RenderString(m_menuItems[i]->Label(), font, point, black);
	}
}

void ruiMenu::Update(rEngine& engine){
}

//--------------------
ruiMenuItem::ruiMenuItem(int id, const rString& label){
	m_id = id;
	m_label = label;
	m_checked = false;
	m_radioId = 0;
}

rString ruiMenuItem::Label() const{
	return m_label;
}