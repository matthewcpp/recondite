#ifndef RUI_TEXTBOX_HPP
#define RUI_TEXTBOX_HPP

#include "rBuild.hpp"

#include "ui/ruiText.hpp"

class RECONDITE_API ruiTextBox : public ruiText{
public:
	
	ruiTextBox(const rString& id, ruiDocument* document, rEngine* engine);
	ruiTextBox(const rString& text, const rString& id, ruiDocument* document, rEngine* engine);

	virtual rString GetWidgetType() const;

public:
	virtual void OnKeyDown(rKey key, const rKeyboardState& keyboard);

private:

};

#endif