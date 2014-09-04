#ifndef RUI_PICKER_HPP
#define RUI_PICKER_HPP

#include "rBuild.hpp"

#include "rEngine.hpp"

#include "ui/ruiBase.hpp"
#include "ui/ruiPickerOptionsMenu.hpp"

#include "ui/ruiEvents.hpp"

class RECONDITE_API ruiPicker : public ruiWidget, public ruiIControlWithOptions{
public:
	ruiPicker(const rString& id, rEngine* engine, const rPoint& position, const rSize& size);
	ruiPicker(rArrayString& options, const rString& id, rEngine* engine, const rPoint& position, const rSize& size);
	
public:
	void AddOption(const rString& option);
	void SetOptions(const rArrayString& options);
	size_t NumOptions() const;

	virtual void OnPointerDown(const rPoint& position);

	virtual size_t SelectionIndex() const;
	virtual bool SetSelectionIndex(size_t index);

	rString SelectionText() const;

	void Clear();

	virtual const rArrayString& Options() const;


	virtual void Draw(rEngine& engine);
	
	void ShowOptionsMenu();

	virtual void SubmenuSelection(size_t index);

private:

	size_t m_selectionIndex;
	rArrayString m_options;
};

#endif
