#ifndef RUI_BASE_HPP
#define RUI_BASE_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

class ruiWidget;

class ruiOverlay{
public:
	virtual void AddWidget(ruiWidget* widget) = 0;
	virtual rContentError LoadOverlay(const rString& path) = 0;
};

class ruiIWidgetManager{
public:
	virtual void ShowModal(ruiWidget* widget) = 0;
	virtual void EndModal(ruiWidget* widget) = 0;
};

class ruiController {
public:
	virtual void Init(ruiOverlay* overlay) = 0;
};

class ruiIControlWithOptions {
public:
	virtual const rArrayString& Options() const = 0;

	virtual size_t SelectionIndex() const = 0;
	virtual bool SetSelectionIndex(size_t index) = 0;
};


#endif
