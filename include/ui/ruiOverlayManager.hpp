#ifndef RUI_OVERLAYMANAGER_HPP
#define RUI_OVERLAYMANAGER_HPP

#include <map>

#include "rBuild.hpp"

#include "rInput.hpp"
#include "rEngine.hpp"

#include "rViewport.hpp"

#include "ui/ruiOverlay.hpp"
#include "ui/ruiWidget.hpp"
#include "ui/ruiBase.hpp"
#include "ui/ruiInterface.hpp"
#include "ui/ruiStyleManager.hpp"
#include "ui/ruiEvents.hpp"
#include "ui/ruiMenu.hpp"

class RECONDITE_API ruiOverlayManager : public ruiIManager {
public:
	ruiOverlayManager();
	~ruiOverlayManager();
	
public:

	virtual bool InsertMouseButtonEvent(rMouseButton button, rButtonState state, const rPoint& position);
	virtual bool InsertMouseWheelEvent(const rPoint& position, rMouseWheelDirection direction);
	virtual bool InsertMouseMotionEvent(const rPoint& point);

	virtual bool InsertTouchEvent(int id, const rPoint& position, rTouchType type);
	virtual bool InsertKeyEvent(rKey key, rKeyState state);
	
	void Update(rEngine& engine);
	void Draw(rViewport* viewport, rEngine& engine);

	void Clear();

	ruiOverlay* CreateOverlay(rViewport* viewport);
	ruiOverlay* GetOverlay(rViewport* viewport) const;

	virtual ruiStyleManager* Styles();
	virtual bool ShowContextMenu(const ruiMenu* menu, rEventHandler* handler);
	virtual void CancelContextMenu();

private:
	rViewport* DetermineViewport(const rPoint& point);
	ruiOverlay* DetermineOverlay(const rPoint& point);

private:
	bool ProcessMouseDown(rMouseButton button, const rPoint& position);
	bool ProcessMouseUp(rMouseButton button, const rPoint& position);

private:
	typedef std::map<rViewport* , ruiOverlay*> ruiViewportOverlayMap;

private:
	ruiViewportOverlayMap m_overlays;
	ruiOverlay* m_activeOverlay;
	
	ruiStyleManager m_styleManager;
};

#endif
