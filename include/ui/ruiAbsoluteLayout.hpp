#ifndef RUI_ABSOLUTELAYOUT_HPP
#define RUI_ABSOLUTELAYOUT_HPP

#include "ruiLayout.hpp"

class ruiAbsoluteLayout : public ruiLayout {
public:
	ruiAbsoluteLayout();

public:
	void SetTop(int top);
	void SetBottom(int bottom);
	void SetLeft(int left);
	void SetRight(int right);

	virtual void Layout(rRect& rect);

private:
	rPoint DetermineLocalOrigin() const;
	rPoint DetermineLayoutItemOrigin(ruiLayoutItem* layoutItem) const;
};

#endif