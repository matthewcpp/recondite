#ifndef RUI_LINEARLAYOUT_HPP
#define RUI_LINEARLAYOUT_HPP

#include "rBuild.hpp"

#include "ruiLayout.hpp"

enum ruiLayoutDirection{
	ruiLAYOUT_HORIZONTAL,
	ruiLAYOUT_VERTICAL
};

class RECONDITE_API ruiLinearLayout : public ruiLayout{
public:
	ruiLinearLayout(ruiLayoutDirection layoutDirection);

public:
	virtual void Layout(rRect& rect);
	virtual rSize Size() const;

	void SetLayoutDirection(ruiLayoutDirection layoutDirection);
	ruiLayoutDirection LayoutDirection() const;

private:
	void LayoutHorizontal(rRect& rect);
	void LayoutVertical(rRect& rect);

private:
	rSize m_cachedSize;
	ruiLayoutDirection m_layoutDirection;
};

#endif