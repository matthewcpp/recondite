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


class RECONDITE_API ruiOverlayManager : public ruiInput {
public:
	ruiOverlayManager();
	~ruiOverlayManager();
	
public:

	virtual bool InjectTouchDown(const rTouch& touch);
	virtual bool InjectTouchMove(const rTouch& touch);
	virtual bool InjectTouchUp(const rTouch& touch);

	virtual bool InjectMouseDownEvent(rMouseButton button, const rMouseState& mouse);
	virtual bool InjectMouseUpEvent(rMouseButton button, const rMouseState& mouse);
	virtual bool InjectMouseMotionEvent(const rMouseState& mouse);
	virtual bool InjectMouseWheelEvent(rMouseWheelDirection direction, const rMouseState& mouse);

	virtual bool InjectKeyDownEvent(rKey key, rKeyboardState& state);
	virtual bool InjectKeyUpEvent(rKey key, rKeyboardState& state);
	
	void Update(rEngine& engine);
	void Draw(rViewport* viewport, rEngine& engine);

	void Clear();

	ruiOverlay* CreateOverlay(rViewport* viewport);
	ruiOverlay* GetOverlay(rViewport* viewport) const;

private:
	rViewport* DetermineViewport(const rPoint& point);

private:
	typedef std::map<rViewport* , ruiOverlay*> ruiViewportOverlayMap;

private:
	ruiViewportOverlayMap m_overlays;

};

#endif
