#ifndef RUI_TEXT_HPP
#define RUI_TEXT_HPP

#include "rBuild.hpp"

#include "ui/ruiWidget.hpp"

class RECONDITE_API ruiText : public ruiWidget {
public:
	ruiText(const rString& id, rEngine* engine);
	ruiText(const rString& text, const rString& id, rEngine* engine);
	
public:
	
	rString GetText() const;
	void SetText(const rString& text);
	
	virtual void Draw(rEngine& engine);
	virtual rString GetWidgetType() const;

protected:
	virtual rSize ComputeSize();

protected:
	rString m_text;
};

#endif