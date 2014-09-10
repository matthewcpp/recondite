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

size_t ruiMenu::NumItems() const{
	return m_menuItems.size();
}

//--------------------
ruiMenuItem::ruiMenuItem(int id, const rString& label){
	m_id = id;
	m_label = label;
}

