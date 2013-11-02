#ifndef RUI_PICKEROPTIONSMENU_HPP
#define RUI_PICKEROPTIONSMENU_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "ui/ruiPickerBase.hpp"
#include "ui/ruiWidget.hpp"

#include "rEngine.hpp"

class ruiPickerOptionsMenu : public ruiWidget{
public:
	ruiPickerOptionsMenu(ruiPickerBase* picker, int id);
	
public:
	virtual void Update(rEngine& engine);
	virtual void Draw(rEngine& engine);
	
private:
	ruiPickerBase* m_picker;
};

#endif