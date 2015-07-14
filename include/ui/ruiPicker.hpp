#ifndef RUI_PICKER_HPP
#define RUI_PICKER_HPP

#include "rBuild.hpp"

#include "rEngine.hpp"

#include "ui/ruiWidget.hpp"

#include "ui/ruiMenu.hpp"
#include "ui/ruiEvents.hpp"


class RECONDITE_API ruiPicker : public ruiWidget{
public:
	ruiPicker(const rString& id, ruiIManager* ui, rEngine* engine);
	ruiPicker(rArrayString& options, const rString& id, ruiIManager* ui, rEngine* engine);
	
public:
	void AddOption(const rString& option);
	void SetOptions(const rArrayString& options);
	virtual const rArrayString& Options() const;
	size_t NumOptions() const;
	void Clear();

	virtual size_t SelectionIndex() const;
	virtual bool SetSelectionIndex(size_t index);
	rString SelectionText() const;

	void ShowOptionsMenu();

public:
	virtual void Draw();

	virtual rString GetWidgetType() const;

protected:
	virtual rSize ComputeSize();
	
private:
	void Init();

private:
	virtual bool OnPointerDown(const rPoint& position);

	void OnSubmenuSelection(rEvent& event);

private:

	size_t m_selectionIndex;
	rArrayString m_options;
};

#endif
