#ifndef RUI_MENU_MANAGER_HPP
#define RUI_MENU_MANAGER_HPP

#include "rBuild.hpp"

#include "rEngine.hpp"
#include "ruiMenu.hpp"
#include "ui/ruiDefaultEventHandler.hpp"
#include "ruiStyle.hpp"

class RECONDITE_API ruiMenuManager : public ruiDefaultEventHandler{
public:
	ruiMenuManager(rEngine* engine);

public:
	bool ShowContextMenu(rViewport* viewport, ruiMenu* menu, ruiStyle* style, const rPoint& position, rEventHandler* handler);
	void CancelContextMenu();

	void Update();
	virtual void Draw();

	virtual bool OnPointerDown(const rPoint& position);

private:
	bool PickMenuItem(const rPoint& position);
	void CalculateMenuSize();
	void AdjustMenuPosition();

private:
	ruiMenu* m_menu;

	rPoint m_position;
	rEventHandler* m_handler;
	ruiStyle* m_style;
	rSize m_menuSize;
	size_t m_rowHeight;
	rEngine* m_engine;
	rViewport* m_viewport;
};

#endif