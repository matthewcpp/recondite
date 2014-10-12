#include "ui/ruiAbsoluteLayout.hpp"

ruiAbsoluteLayout::ruiAbsoluteLayout(){
	m_properties.SetInt("top", 0);
	m_properties.SetInt("left", 0);

	m_properties.SetInt("bottom", -1);
	m_properties.SetInt("right", -1);
}

void ruiAbsoluteLayout::Layout(rRect& rect){
	rPoint localOrigin = DetermineLocalOrigin();

	for (size_t i = 0; i < m_layoutItems.size(); i++){
		ruiLayoutItem* layoutItem = m_layoutItems[i];

		rSize itemSize = layoutItem->GetSize();
		rPoint itemOrigin = DetermineLayoutItemOrigin(layoutItem);
		layoutItem->SetPosition(localOrigin + itemOrigin);
	}
}

//TODO: make these methods actually take into account right and bottom
rPoint ruiAbsoluteLayout::DetermineLocalOrigin() const{
	int top = 0;
	int left = 0;

	m_properties.GetInt("top", top);
	m_properties.GetInt("left", left);

	return rPoint(top, left);
}

rPoint ruiAbsoluteLayout::DetermineLayoutItemOrigin(ruiLayoutItem* layoutItem) const{
	int top = 0;
	int left = 0;

	const rPropertyCollection* properties = layoutItem->Properties();

	properties->GetInt("top", top);
	properties->GetInt("left", left);

	return rPoint(top, left);
}

//-----

void ruiAbsoluteLayout::SetTop(int top){
	m_properties.SetInt("top", 0);
}

void ruiAbsoluteLayout::SetBottom(int bottom){
	m_properties.SetInt("bottom", -1);
}

void ruiAbsoluteLayout::SetLeft(int left){
	m_properties.SetInt("left", 0);
}

void ruiAbsoluteLayout::SetRight(int right){
	m_properties.SetInt("right", -1);
}