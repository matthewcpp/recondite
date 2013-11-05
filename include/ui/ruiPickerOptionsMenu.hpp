#ifndef RUI_PICKEROPTIONSMENU_HPP
#define RUI_PICKEROPTIONSMENU_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "ui/ruiWidget.hpp"

#include "rEngine.hpp"

class ruiIControlWithOptions {
public:
	virtual const rArrayString& Options() const = 0;

	virtual size_t SelectionIndex() const = 0;
	virtual bool SetSelectionIndex(size_t index) = 0;
};

class ruiPickerOptionsMenu : public ruiWidget{
public:
	ruiPickerOptionsMenu(ruiIControlWithOptions* picker, ruiIWidgetManager* manager, int id);
	
public:
	virtual void OnTouchDown(const rTouch& touch);

	virtual void Draw(rEngine& engine);
	
private:
	ruiIControlWithOptions* m_picker;
	ruiIWidgetManager* m_manager;
};

#endif
