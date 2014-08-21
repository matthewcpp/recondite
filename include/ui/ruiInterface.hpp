#ifndef RUI_INTERFACE_HPP
#define RUI_INTERFACE_HPP

#include "rBuild.hpp"

#include "ui/ruiStyleManager.hpp"

class RECONDITE_API ruiIManager {
public:
	virtual ruiStyleManager* Styles() = 0;
};

#endif