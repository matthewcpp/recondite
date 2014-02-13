#ifndef RUI_TEXT_HPP
#define RUI_TEXT_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "ui/ruiWidget.hpp"

class ruiText : public ruiWidget {
public:
	ruiText(int id, const rPoint& position, const rSize& size);
	ruiText(const rString& text, int id, const rPoint& position, const rSize& size);
	
public:
	
	rString GetText() const;
	void SetText(const rString& text);
	
	virtual void Draw(rEngine& engine);

protected:
	rString m_text;
	rSize m_cachedSize;
};

#endif