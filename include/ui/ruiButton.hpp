#ifndef RUI_BUTTON_HPP
#define RUI_BUTTON_HPP

#include "rString.hpp"
#include "rBuild.hpp"

#include "ui/ruiWidget.hpp"
#include "ui/ruiEvents.hpp"

class RECONDITE_API ruiButton : public ruiWidget{
public:
	ruiButton(const rString& text, const rString& id, rEngine* engine, const rPoint& position, const rSize& size);
	
public:
	rString GetText() const;
	void SetText(const rString& text);

	virtual void Draw(rEngine& engine);
	rButtonState ButtonState() const;

private:
	void OnPointerDown(const rPoint& position);
	void OnPointerUp(const rPoint& position);
	void OnPointerLeave(const rPoint& position);
	void OnPointerEnter(const rPoint& position);

	void OnMouseDown(rEvent& event);
	void OnMouseUp(rEvent& event);
	void OnMouseLeave(rEvent& event);
	void OnMouseEnter(rEvent& event);
	
private:
	
	rButtonState m_state;
	
	rString m_text;
	rSize m_cachedSize;
};

#endif
