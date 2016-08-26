#include "ui/ruiAbsoluteLayout.hpp"
#include "ui/ruiDocument.hpp"

ruiAbsoluteLayout::ruiAbsoluteLayout(const rString& id, ruiIDocument* document, rEngine* engine)
:ruiLayout(id, document, engine)
{}

void UpdatePoints(rPoint& ptmin, rPoint& ptmax, const rPoint& pos) {
	ptmin.Set(std::min(ptmin.x, pos.x), std::min(ptmin.y, pos.y));
	ptmax.Set(std::max(ptmin.x, pos.x), std::max(ptmin.y, pos.y));
}

rSize ruiAbsoluteLayout::Layout(rRect& rect){
	if (m_layoutItems.size() == 0) return rSize(0, 0);

	rPoint ptmin(INT32_MAX, INT32_MAX);
	rPoint ptmax(INT32_MIN, INT32_MIN);

	for (size_t i = 0; i < m_layoutItems.size(); i++){	
		ruiWidget* widget = m_layoutItems[i];
		int margins[4] = { 0, 0, 0, 0 };

		int top = 0;
		int left = 0;
		int bottom = 0;
		int right = 0;

		ruiStyle* properties = widget->ComputedStyle();

		bool hasTop = properties->GetInt("top", top);
		bool hasLeft = properties->GetInt("left", left);
		bool hasBottom = properties->GetInt("bottom", bottom);
		bool hasRight = properties->GetInt("right", right);

		rSize itemSize = widget->Size();
		
		rPoint position;

		if (hasTop)
			position.y = top;

		else if (hasBottom)
			position.y = rect.Bottom() - bottom - itemSize.y;
		else
			position.y = 0;
			

		if (hasLeft)
			position.x = left;
		else if (hasRight)
			position.x = rect.Right() - right - itemSize.x;
		else
			position.x = 0;
			
		widget->SetPosition(position);

		UpdatePoints(ptmin, ptmax, position);
		UpdatePoints(ptmin, ptmax, rPoint(position.x + itemSize.x, position.y + itemSize.y));
	}

	rPoint difference = ptmax - ptmin;
	return rSize(difference.x, difference.y);
}

void ruiAbsoluteLayout::SetPosition(const rPoint& position) {
	ruiWidget::SetPosition(position);
	Layout(m_document->GetViewport()->GetScreenRect());
}

rString ruiAbsoluteLayout::GetWidgetType() const {
	return "absolutelayout";
}

//-----