#ifndef RUI_MENU_MANAGER_HPP
#define RUI_MENU_MANAGER_HPP

#include "rBuild.hpp"

#include "rEngine.hpp"
#include "ruiMenu.hpp"
#include "ruiWidgetBase.hpp"
#include "ui/ruiDefaultEventHandler.hpp"

class RECONDITE_API ruiMenuManager : public ruiDefaultEventHandler{
public:
	ruiMenuManager();

public:
	bool ShowContextMenu(ruiMenu* menu, ruiStyle* style, const rPoint& position, rEventHandler* handler);
	void CancelContextMenu();

	void Update(rEngine& engine);
	virtual void Draw(rEngine& engine);

private:
	bool PickMenuItem(const rPoint& position);
	ruiStyle* GetStyle();

private:
	virtual bool OnPointerDown(const rPoint& position);

private:
	ruiMenu* m_menu;
	rPoint m_position;
	rEventHandler* m_handler;
	ruiStyle* m_style;

	ruiStyle m_defaultStyle;
};

#endif