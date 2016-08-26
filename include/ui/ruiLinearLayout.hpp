#ifndef RUI_LINEARLAYOUT_HPP
#define RUI_LINEARLAYOUT_HPP

#include <algorithm>

#include "rBuild.hpp"
#include "rTypes.hpp"

#include "ruiLayout.hpp"
#include "rEngine.hpp"

enum ruiLayoutDirection{
	ruiLAYOUT_HORIZONTAL,
	ruiLAYOUT_VERTICAL
};

enum ruiMargin{
	ruiMARGIN_TOP,
	ruiMARGIN_RIGHT,
	ruiMARGIN_BOTTOM,
	ruiMARGIN_LEFT
};

class RECONDITE_API ruiLinearLayout : public ruiLayout{
public:
	ruiLinearLayout(ruiLayoutDirection layoutDirection, const rString& id, ruiIDocument* document, rEngine* engine);

public:
	virtual rSize Layout(rRect& rect);

	void SetLayoutDirection(ruiLayoutDirection layoutDirection);
	ruiLayoutDirection LayoutDirection() const;

	virtual rString GetWidgetType() const;

	virtual void SetPosition(const rPoint& position);

private:
	rSize LayoutHorizontal(rRect& rect);
	rSize LayoutVertical(rRect& rect);

	void DetermineMargins(ruiWidget* widget, rIntArray& margins);

private:
	ruiLayoutDirection m_layoutDirection;
};

#endif