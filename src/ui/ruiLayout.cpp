#include "ui/ruiLayout.hpp"

ruiWidgetLayoutItem::ruiWidgetLayoutItem(ruiWidget* widget, size_t flags)
	:ruiLayoutItem(flags)
{
	m_widget = widget;
}

rSize ruiWidgetLayoutItem::GetSize() const{
	return m_widget->Size();
}

void ruiWidgetLayoutItem::SetPosition(const rPoint& position){
	m_widget->SetPosition(position);
}

const rPropertyCollection* ruiWidgetLayoutItem::Properties() const{
	return m_widget->ComputedStyle();
}

//--------------------

ruiLayoutLayoutItem::ruiLayoutLayoutItem(ruiLayout* layout, size_t flags)
	:ruiLayoutItem(flags)
{
	m_layout = layout;
}

rSize ruiLayoutLayoutItem::GetSize() const{
	return m_layout->Size();
}

void ruiLayoutLayoutItem::SetPosition(const rPoint& position){
	m_layout->SetPosition(position);
}

const rPropertyCollection* ruiLayoutLayoutItem::Properties() const{
	return m_layout->Properties();
}

//--------------------

ruiLayout::~ruiLayout(){
	Clear();
}

void ruiLayout::Clear(){
	for (size_t i = 0; i < m_layoutItems.size(); i++)
		delete m_layoutItems[i];

	m_layoutItems.clear();
}

void ruiLayout::AddItem(ruiWidget* widget, size_t flags){
	m_layoutItems.push_back(new ruiWidgetLayoutItem(widget, flags));
}

void ruiLayout::AddItem(ruiLayout* layout, size_t flags){
	m_layoutItems.push_back(new ruiLayoutLayoutItem(layout, flags));
}

size_t ruiLayout::ItemCount() const{
	return m_layoutItems.size();
}

void ruiLayout::SetPosition(const rPoint& position){
	m_position = position;
}

rPoint ruiLayout::Position() const{
	return m_position;
}

const rPropertyCollection* ruiLayout::Properties() const{
	return &m_properties;
}