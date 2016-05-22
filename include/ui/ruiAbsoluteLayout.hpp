#ifndef RUI_ABSOLUTELAYOUT_HPP
#define RUI_ABSOLUTELAYOUT_HPP

#include "ruiLayout.hpp"

class RECONDITE_API ruiAbsoluteLayout : public ruiLayout {
public:
	ruiAbsoluteLayout();

public:
	void SetTop(int top);
	void SetBottom(int bottom);
	void SetLeft(int left);
	void SetRight(int right);

	virtual void Layout(rRect& rect);
	virtual rSize Size() const;

};

#endif