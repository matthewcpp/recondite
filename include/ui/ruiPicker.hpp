#ifndef RUI_PICKER_HPP
#define RUI_PICKER_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "ui/ruiPickerBase.hpp"
#include "rEngine.hpp"

#include "ruiPickerOptionsMenu.hpp"

class ruiPicker : public ruiPickerBase{
public:
	ruiPicker(int id, const rPoint& position, const rSize& size);
	ruiPicker(rArrayString& options, int id, const rPoint& position, const rSize& size);
	
public:

	virtual void Update(rEngine& engine);
	virtual void Draw(rEngine& engine);
	
	void ShowOptionsMenu();
	void HideOptionsMenu();

	virtual void SubmenuSelection(size_t index);

private:

	ruiPickerOptionsMenu* m_optionsMenu;
};

#endif
