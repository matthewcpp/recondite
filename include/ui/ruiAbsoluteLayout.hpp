#ifndef RUI_ABSOLUTELAYOUT_HPP
#define RUI_ABSOLUTELAYOUT_HPP

#include "ruiLayout.hpp"

class RECONDITE_API ruiAbsoluteLayout : public ruiLayout {
public:
	ruiAbsoluteLayout(const rString& id, ruiIDocument* document, rEngine* engine);

public:
	virtual rSize Layout(rRect& rect);
	virtual rString GetWidgetType() const;

	virtual void SetPosition(const rPoint& position);

};

#endif