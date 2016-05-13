#ifndef RUI_OVERLAYMANAGER_HPP
#define RUI_OVERLAYMANAGER_HPP

#include <map>

#include "rBuild.hpp"

#include "rInput.hpp"
#include "rEngine.hpp"

#include "rViewport.hpp"

#include "ui/ruiOverlay.hpp"
#include "ui/ruiInterface.hpp"
#include "ui/ruiEvents.hpp"
#include "ui/ruiMenuManager.hpp"

class RECONDITE_API ruiOverlayManager : public ruiIManager {
public:
	ruiOverlayManager(rEngine* engine);
	~ruiOverlayManager();
	
public:

	virtual bool InsertMouseButtonEvent(rMouseButton button, rButtonState state, const rPoint& position);
	virtual bool InsertMouseWheelEvent(const rPoint& position, rMouseWheelDirection direction);
	virtual bool InsertMouseMotionEvent(const rPoint& point);

	virtual bool InsertTouchEvent(int id, const rPoint& position, rTouchType type);
	virtual bool InsertKeyEvent(rKey key, rKeyState state);
	
	void Update();
	void Draw(rViewport* viewport);

	void Clear();

	virtual ruiOverlay* CreateOverlay(rViewport* viewport);
	virtual ruiOverlay* LoadOverlay(const rString& filePath, rViewport* viewport);
	virtual ruiOverlay* GetOverlay(rViewport* viewport) const;

private:
	rViewport* DetermineViewport(const rPoint& point);
	ruiOverlay* DetermineOverlay(const rPoint& point);
	void AddOverlayToViewport(ruiOverlay* overlay, rViewport* viewport);

private:
	bool ProcessMouseDown(rMouseButton button, const rPoint& position);
	bool ProcessMouseUp(rMouseButton button, const rPoint& position);

private:
	typedef std::map<rViewport* , ruiOverlay*> ruiViewportOverlayMap;

private:
	ruiViewportOverlayMap m_overlays;
	ruiOverlay* m_activeOverlay;
	rEngine* m_engine;
};

#endif
