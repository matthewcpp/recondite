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
	rIntArray margins(4);

	for (size_t i = 0; i < m_layoutItems.size(); i++){
		layoutItem = m_layoutItems[i];
		DetermineMargins(layoutItem, margins);

		rPoint finalPosition = layoutPos;
		finalPosition.x += margins[ruiMARGIN_LEFT];
		finalPosition.y += margins[ruiMARGIN_TOP];
		layoutItem->SetPosition(finalPosition);

		currentItemSize = layoutItem->GetSize();
		m_cachedSize.x += currentItemSize.x + margins[ruiMARGIN_LEFT] + margins[ruiMARGIN_RIGHT];
		m_cachedSize.y = std::max(m_cachedSize.y, currentItemSize.y + margins[ruiMARGIN_TOP] + margins[ruiMARGIN_BOTTOM]);
		layoutPos.x += currentItemSize.x + margins[ruiMARGIN_LEFT] + margins[ruiMARGIN_RIGHT];
	}
}

void ruiLinearLayout::LayoutVertical(rRect& rect){
	rSize currentItemSize(0, 0);
	ruiLayoutItem* layoutItem = NULL;
	rPoint layoutPos(rect.x, rect.y);
	rIntArray margins(4);

	for (size_t i = 0; i < m_layoutItems.size(); i++){
		layoutItem = m_layoutItems[i];
		DetermineMargins(layoutItem, margins);
		
		rPoint finalPosition = layoutPos;
		finalPosition.x += margins[ruiMARGIN_LEFT];
		finalPosition.y += margins[ruiMARGIN_TOP];
		layoutItem->SetPosition(finalPosition);

		currentItemSize = layoutItem->GetSize();
		m_cachedSize.x += std::max(m_cachedSize.x, currentItemSize.x + margins[ruiMARGIN_LEFT] + margins[ruiMARGIN_RIGHT]);
		m_cachedSize.y = currentItemSize.y + margins[ruiMARGIN_TOP] + margins[ruiMARGIN_BOTTOM];
		layoutPos.y += currentItemSize.y + margins[ruiMARGIN_TOP] + margins[ruiMARGIN_BOTTOM];
	}
}

void ruiLinearLayout::DetermineMargins(ruiLayoutItem* layoutItem, rIntArray& margins){
	std::fill(margins.begin(), margins.end(), 0);

	const rPropertyCollection* properties = layoutItem->Properties();

	properties->GetInt("margin-top", margins[ruiMARGIN_TOP]);
	properties->GetInt("margin-right", margins[ruiMARGIN_RIGHT]);
	properties->GetInt("margin-bottom", margins[ruiMARGIN_BOTTOM]);
	properties->GetInt("margin-left", margins[ruiMARGIN_LEFT]);
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