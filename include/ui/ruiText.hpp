#ifndef RUI_TEXT_HPP
#define RUI_TEXT_HPP

#include "rBuild.hpp"

#include "ui/ruiWidget.hpp"

class RECONDITE_API ruiText : public ruiWidget {
public:
	ruiText(const rString& id, ruiIDocument* document, rEngine* engine);
	ruiText(const rString& text, const rString& id, ruiIDocument* document, rEngine* engine);
	
public:
	
	rString GetText() const;
	void SetText(const rString& text);
	
	virtual void Draw();
	virtual rString GetWidgetType() const;

protected:
	virtual rSize ComputeSize();

protected:
	rString m_text;
	rSize m_cachedStringSize;
};

#endif