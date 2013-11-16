#ifndef RUI_PICKER_HPP
#define RUI_PICKER_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rEngine.hpp"

#include "ui/ruiBase.hpp"
#include "ui/ruiPickerOptionsMenu.hpp"

#include "ui/ruiEventType.hpp"

class ruiPicker : public ruiWidget, public ruiIControlWithOptions{
public:
	ruiPicker(int id, const rPoint& position, const rSize& size);
	ruiPicker(rArrayString& options, int id, const rPoint& position, const rSize& size);
	
public:
	void AddOption(const rString& option);
	void SetOptions(const rArrayString& options);
	size_t NumOptions() const;

	virtual size_t SelectionIndex() const;
	virtual bool SetSelectionIndex(size_t index);

	rString SelectionText() const;

	void Clear();

	virtual const rArrayString& Options() const;

	virtual void OnTouchDown(const rTouch& touch);

	virtual void Draw(rEngine& engine);
	
	void ShowOptionsMenu();

	virtual void SubmenuSelection(size_t index);

private:

	size_t m_selectionIndex;
	rArrayString m_options;
};

#endif