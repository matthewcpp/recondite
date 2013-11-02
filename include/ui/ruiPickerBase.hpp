#ifndef RUI_PICKERBASE_HPP
#define RUI_PICKERBASE_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "ui/ruiWidget.hpp"

class ruiPickerBase : public ruiWidget{
public:

	ruiPickerBase(int id, const rPoint& position, const rSize& size);
	ruiPickerBase(rArrayString& options, int id, const rPoint& position, const rSize& size);

	void AddOption(const rString& option);
	void SetOptions(const rArrayString& options);
	size_t NumOptions() const;
	
	size_t SelectionIndex() const;
	bool SetSelectionIndex(size_t index);
	
	rString SelectionText() const;
	
	void Clear();

	const rArrayString& Options() const;

	virtual void SubmenuSelection(size_t index) = 0;

protected:

	size_t m_selectionIndex;
	rArrayString m_options;
};

#endif
