#ifndef RUI_TEXTBOX_HPP
#define RUI_TEXTBOX_HPP

#include "rBuild.hpp"

#include "ui/ruiText.hpp"

class RECONDITE_API ruiTextBox : public ruiText{
public:
	
	ruiTextBox(const rString& id, rEngine* engine, const rPoint& position, const rSize& size);
	ruiTextBox(const rString& text, const rString& id, rEngine* engine, const rPoint& position, const rSize& size);

	virtual rString GetWidgetType() const;

public:
	virtual void OnKeyDown(rKey key, const rKeyboardState& keyboard);

private:

};

#endif