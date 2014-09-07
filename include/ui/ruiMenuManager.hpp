#ifndef RUI_MENU_MANAGER_HPP
#define RUI_MENU_MANAGER_HPP

#include "rBuild.hpp"

#include "rEngine.hpp"
#include "ruiMenu.hpp"
#include "ruiWidgetBase.hpp"
#include "rEventHandler.hpp"

class RECONDITE_API ruiMenuManager : public rEventHandler{
public:
	ruiMenuManager();

public:
	bool ShowContextMenu(const ruiMenu* menu, const rPoint& position, rEventHandler* handler);
	void CancelContextMenu();

	void Update(rEngine& engine);
	virtual void Draw(rEngine& engine);

private:

};

#endif