#include "ui/ruiAbsoluteLayout.hpp"

ruiAbsoluteLayout::ruiAbsoluteLayout() {
	m_properties.SetInt("top", 0);
	m_properties.SetInt("left", 0);
}

void ruiAbsoluteLayout::Layout(rRect& rect){
	for (size_t i = 0; i < m_layoutItems.size(); i++){	
		ruiLayoutItem* layoutItem = m_layoutItems[i];
		int margins[4] = { 0, 0, 0, 0 };

		int top = 0;
		int left = 0;
		int bottom = 0;
		int right = 0;

		const rPropertyCollection* properties = layoutItem->Properties();

		bool hasTop = properties->GetInt("top", top);
		bool hasLeft = properties->GetInt("left", left);
		bool hasBottom = properties->GetInt("bottom", bottom);
		bool hasRight = properties->GetInt("right", right);

		rSize itemSize = layoutItem->GetSize();
		rPoint position(rect.Left(), rect.Top());

		if (hasTop)
			position.y = top;
		else if (hasBottom)
			position.y = rect.Bottom() - bottom - itemSize.y;

		if (hasLeft)
			position.x = left;
		else if (hasRight)
			position.x = rect.Right() - right - itemSize.x;
			
		layoutItem->SetPosition(position);
	}
}

rSize ruiAbsoluteLayout::Size() const{
	return rSize(0,0);
}

//-----

void ruiAbsoluteLayout::SetTop(int top){
	m_properties.SetInt("top", top);
}

void ruiAbsoluteLayout::SetBottom(int bottom){
	m_properties.SetInt("bottom", bottom);
}

void ruiAbsoluteLayout::SetLeft(int left){
	m_properties.SetInt("left", left);
}

void ruiAbsoluteLayout::SetRight(int right){
	m_properties.SetInt("right", right);
}