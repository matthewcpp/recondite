#include "ui/ruiLinearLayout.hpp"

ruiLinearLayout::ruiLinearLayout(ruiLayoutDirection layoutDirection, const rString& id, ruiIDocument* document, rEngine* engine) 
	:ruiLayout(id,document, engine){
	SetLayoutDirection(layoutDirection);
}

void ruiLinearLayout::SetPosition(const rPoint& position) {
	ruiWidget::SetPosition(position);

	Layout(rRect(m_position, rSize::Default));
}

rSize ruiLinearLayout::Layout(rRect& rect){
	rSize size;

	if (m_layoutDirection == ruiLAYOUT_HORIZONTAL)
		size = LayoutHorizontal(rect);
	else
		size = LayoutVertical(rect);

	return size;
}

rSize ruiLinearLayout::ComputeSize() {
	rRect testRect(0, 0, INT_MAX, INT_MAX);

	if (m_layoutDirection == ruiLAYOUT_HORIZONTAL) {
		return LayoutHorizontal(testRect, false);
	}
	else {
		return LayoutVertical(testRect, false);
	}
}

rSize ruiLinearLayout::LayoutHorizontal(rRect& rect, bool setPosition){
	rSize layoutSize(0, 0);
	rSize currentItemSize(0, 0);
	
	ruiWidget* widget = nullptr;
	rPoint contentOffset = ContentOffset();
	rPoint layoutPos(rect.x + contentOffset.x, rect.y+ contentOffset.y);
	rIntArray margins(4);

	for (size_t i = 0; i < m_layoutItems.size(); i++){
		widget = m_layoutItems[i];
		DetermineMargins(widget, margins);

		rPoint finalPosition = layoutPos;
		finalPosition.x += margins[ruiMARGIN_LEFT];
		finalPosition.y += margins[ruiMARGIN_TOP];
		if (setPosition)
			widget->SetPosition(finalPosition);

		currentItemSize = widget->Size();
		layoutSize.x += currentItemSize.x + margins[ruiMARGIN_LEFT] + margins[ruiMARGIN_RIGHT];
		layoutSize.y = std::max(layoutSize.y, currentItemSize.y + margins[ruiMARGIN_TOP] + margins[ruiMARGIN_BOTTOM]);
		layoutPos.x += currentItemSize.x + margins[ruiMARGIN_LEFT] + margins[ruiMARGIN_RIGHT];
	}

	return layoutSize;
}

rSize ruiLinearLayout::LayoutVertical(rRect& rect, bool setPosition){
	rSize layoutSize(0, 0);
	rSize currentItemSize(0, 0);

	ruiWidget* widget = nullptr;
	rPoint contentOffset = ContentOffset();
	rPoint layoutPos(rect.x + contentOffset.x, rect.y + contentOffset.y);
	rIntArray margins(4);

	for (size_t i = 0; i < m_layoutItems.size(); i++){
		widget = m_layoutItems[i];
		DetermineMargins(widget, margins);
		
		rPoint finalPosition = layoutPos;
		finalPosition.x += margins[ruiMARGIN_LEFT];
		finalPosition.y += margins[ruiMARGIN_TOP];

		if (setPosition)
			widget->SetPosition(finalPosition);

		currentItemSize = widget->Size();
		layoutSize.x = std::max(layoutSize.x, currentItemSize.x + margins[ruiMARGIN_LEFT] + margins[ruiMARGIN_RIGHT]);
		layoutSize.y += currentItemSize.y + margins[ruiMARGIN_TOP] + margins[ruiMARGIN_BOTTOM];
		layoutPos.y += currentItemSize.y + margins[ruiMARGIN_TOP] + margins[ruiMARGIN_BOTTOM];
	}

	return layoutSize;
}

void ruiLinearLayout::DetermineMargins(ruiWidget* widget, rIntArray& margins){
	std::fill(margins.begin(), margins.end(), 0);

	const ruiStyle* properties = widget->ComputedStyle();

	properties->GetInt("margin-top", margins[ruiMARGIN_TOP]);
	properties->GetInt("margin-right", margins[ruiMARGIN_RIGHT]);
	properties->GetInt("margin-bottom", margins[ruiMARGIN_BOTTOM]);
	properties->GetInt("margin-left", margins[ruiMARGIN_LEFT]);
}

void ruiLinearLayout::SetLayoutDirection(ruiLayoutDirection layoutDirection){
	m_layoutDirection = layoutDirection;
}

ruiLayoutDirection ruiLinearLayout::LayoutDirection() const{
	return m_layoutDirection;
}

rString ruiLinearLayout::GetWidgetType() const {
	return "linearlayout";
}