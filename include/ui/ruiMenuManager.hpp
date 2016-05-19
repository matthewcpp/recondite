#ifndef RUI_MENU_MANAGER_HPP
#define RUI_MENU_MANAGER_HPP

#include "rBuild.hpp"

#include "rEngine.hpp"
#include "ruiMenu.hpp"
#include "ruiWidgetBase.hpp"
#include "ui/ruiDefaultEventHandler.hpp"

class RECONDITE_API ruiMenuManager : public ruiDefaultEventHandler{
public:
	ruiMenuManager(rEngine* engine);

public:
	bool ShowContextMenu(ruiMenu* menu, ruiStyle* style, const rPoint& position, rEventHandler* handler);
	void CancelContextMenu();

	void Update();
	virtual void Draw();

	virtual bool OnPointerDown(const rPoint& position);

private:
	bool PickMenuItem(const rPoint& position);
	void CalculateMenuSize();

private:
	ruiMenu* m_menu;

	rPoint m_position;
	rEventHandler* m_handler;
	ruiStyle* m_style;
	rSize m_menuSize;
	size_t m_rowHeight;
	rEngine* m_engine;
};

#endif