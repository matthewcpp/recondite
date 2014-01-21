#ifndef RUI_PICKEROPTIONSMENU_HPP
#define RUI_PICKEROPTIONSMENU_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "ui/ruiWidget.hpp"
#include "ui/ruiBase.hpp"

#include "rEngine.hpp"


class ruiPickerOptionsMenu : public ruiWidget{
public:
	ruiPickerOptionsMenu(ruiIControlWithOptions* picker, int id);
	
public:
	virtual void OnPointerDown(const rPoint& position);

	virtual void Draw(rEngine& engine);
	
private:
	ruiIControlWithOptions* m_picker;
};

#endif
