#ifndef RUI_BUTTON_HPP
#define RUI_BUTTON_HPP

#include "rString.hpp"
#include "rBuild.hpp"

#include "ui/ruiWidget.hpp"
#include "ui/ruiEvents.hpp"

class RECONDITE_API ruiButton : public ruiWidget{
public:
	ruiButton(const rString& text, const rString& id, ruiDocument* document, rEngine* engine);
	
public:
	rString GetText() const;
	void SetText(const rString& text);

	virtual void Draw();
	rButtonState ButtonState() const;

	virtual rString GetWidgetType() const;

protected:
	virtual rSize ComputeSize();

protected:
	virtual bool OnPointerDown(const rPoint& position);
	virtual bool OnPointerUp(const rPoint& position);
	virtual bool OnPointerLeave(const rPoint& position);
	virtual bool OnPointerEnter(const rPoint& position);

	
private:
	
	rButtonState m_state;
	
	rString m_text;
};

#endif
