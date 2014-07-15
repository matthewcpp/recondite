#ifndef RUI_INTERFACE_HPP
#define RUI_INTERFACE_HPP

#include "rBuild.hpp"

#include "ui/ruiStyleManager.hpp"
#include "ui/ruiWidgetBase.hpp"

class RECONDITE_API ruiWidget;

class RECONDITE_API ruiIOverlay {
public:
	virtual void ShowModal(ruiWidget* widget) = 0;
	virtual void EndModal(ruiWidget* widget) = 0;
};

class RECONDITE_API ruiIManager {
public:
	virtual ruiIOverlay* ActiveOverlay() = 0;
	virtual ruiStyleManager* Styles() = 0;
};

#endif