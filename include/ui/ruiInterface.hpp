#ifndef RUI_INTERFACE_HPP
#define RUI_INTERFACE_HPP

#include "rBuild.hpp"

#include "rEventHandler.hpp"

#include "ui/ruiStyleManager.hpp"

class ruiMenu;
class ruiOverlay;

class RECONDITE_API ruiIManager {
public:
	virtual ruiOverlay* CreateOverlay(rViewport* viewport) = 0;
	virtual ruiOverlay* LoadOverlay(const rString& filePath, rViewport* viewport) = 0;
	virtual ruiOverlay* GetOverlay(rViewport* viewport) const = 0;
};

#endif