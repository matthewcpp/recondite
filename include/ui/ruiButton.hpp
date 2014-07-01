#ifndef RUI_BUTTON_HPP
#define RUI_BUTTON_HPP

#include "rString.hpp"
#include "rBuild.hpp"

#include "ui/ruiWidget.hpp"
#include "ui/ruiEventType.hpp"

class RECONDITE_API ruiButton : public ruiWidget{
public:
	ruiButton(const rString& text, const rString& id, rEngine* engine, const rPoint& position, const rSize& size);
	
public:
	
	rString GetText() const;
	void SetText(const rString& text);
	
	virtual void OnPointerDown(const rPoint& position);
	virtual void OnPointerUp(const rPoint& position);

	virtual void Draw(rEngine& engine);
	
	rButtonState GetState() const;
	
private:
	
	rButtonState m_state;
	
	rString m_text;
	rSize m_cachedSize;
};

#endif
