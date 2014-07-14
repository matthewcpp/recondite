#ifndef RUI_PICKEROPTIONSMENU_HPP
#define RUI_PICKEROPTIONSMENU_HPP

#include "rBuild.hpp"

#include "ui/ruiWidget.hpp"
#include "ui/ruiBase.hpp"

#include "rEngine.hpp"


class RECONDITE_API ruiPickerOptionsMenu : public ruiWidget{
public:
	ruiPickerOptionsMenu(ruiIControlWithOptions* picker, const rString& id, ruiIOverlay* overlay, rEngine* engine);
	
public:
	virtual void OnPointerDown(const rPoint& position);

	virtual void Draw(rEngine& engine);
	
private:
	ruiIControlWithOptions* m_picker;
};

#endif
