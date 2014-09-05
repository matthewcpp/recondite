#ifndef RUI_CHECKBOX_HPP
#define RUI_CHECKBOX_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "ruiWidget.hpp"
#include "ui/ruiEvents.hpp"

class ruiCheckbox : public ruiWidget{
public:
	ruiCheckbox(const rString& id, rEngine* engine, const rPoint& position, const rSize& size);
	
public:

	bool IsChecked () const;
	void SetChecked(bool checked);
	
	virtual void Draw(rEngine& engine);

public:

	void OnMouseDown(rEvent& event);
	void OnPointerDown(const rPoint& position);
	
private:
	bool m_isChecked;
};


#endif
