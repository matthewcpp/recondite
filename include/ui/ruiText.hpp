#ifndef RUI_TEXT_HPP
#define RUI_TEXT_HPP

#include "rBuild.hpp"

#include "ui/ruiWidget.hpp"

class RECONDITE_API ruiText : public ruiWidget {
public:
	ruiText(const rString& id, rEngine* engine, const rPoint& position, const rSize& size);
	ruiText(const rString& text, const rString& id, rEngine* engine, const rPoint& position, const rSize& size);
	
public:
	
	rString GetText() const;
	void SetText(const rString& text);
	
	virtual void Draw(rEngine& engine);

protected:
	rString m_text;
	rSize m_cachedSize;
};

#endif