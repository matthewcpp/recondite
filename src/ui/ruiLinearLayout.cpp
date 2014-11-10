#include "ui/ruiLinearLayout.hpp"

ruiLinearLayout::ruiLinearLayout(ruiLayoutDirection layoutDirection){
	m_cachedSize.Set(0, 0);
	SetLayoutDirection(layoutDirection);
}

void ruiLinearLayout::Layout(rRect& rect){
	m_cachedSize.Set(0, 0);

	if (m_layoutDirection == ruiLAYOUT_HORIZONTAL)
		LayoutHorizontal(rect);
	else
		LayoutVertical(rect);
}

void ruiLinearLayout::LayoutHorizontal(rRect& rect){
	rSize currentItemSize(0, 0);
	ruiLayoutItem* layoutItem = NULL;
	rPoint layoutPos(rect.x, rect.y);

	for (size_t i = 0; i < m_layoutItems.size(); i++){
		layoutItem = m_layoutItems[i];
		layoutItem->SetPosition(layoutPos);

		currentItemSize = layoutItem->GetSize();
		m_cachedSize.x += currentItemSize.x;
		m_cachedSize.y = std::max(m_cachedSize.y, currentItemSize.y);
		layoutPos.x += currentItemSize.x;
	}
}

void ruiLinearLayout::LayoutVertical(rRect& rect){
	rSize currentItemSize(0, 0);
	ruiLayoutItem* layoutItem = NULL;
	rPoint layoutPos(rect.x, rect.y);

	for (size_t i = 0; i < m_layoutItems.size(); i++){
		layoutItem = m_layoutItems[i];
		layoutItem->SetPosition(layoutPos);

		currentItemSize = layoutItem->GetSize();
		m_cachedSize.x += std::max(m_cachedSize.y, currentItemSize.y);
		m_cachedSize.y = currentItemSize.y;
		layoutPos.y += currentItemSize.y;
	}
}

rSize ruiLinearLayout::Size() const{
	return m_cachedSize;
}

void ruiLinearLayout::SetLayoutDirection(ruiLayoutDirection layoutDirection){
	m_layoutDirection = layoutDirection;
}

ruiLayoutDirection ruiLinearLayout::LayoutDirection() const{
	return m_layoutDirection;
}