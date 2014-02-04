#ifndef RUI_LAYOUTMANAGER_HPP
#define RUI_LAYOUTMANAGER_HPP

#include <map>

#include "rInput.hpp"
#include "rEngine.hpp"

#include "rViewport.hpp"

#include "ui/ruiOverlay.hpp"
#include "ui/ruiWidget.hpp"
#include "ui/ruiBase.hpp"

typedef std::map<rViewport* , ruiOverlay*> ruiViewportOverlayMap;


class ruiLayoutManager : public ruiInput {
public:
	ruiLayoutManager();
	~ruiLayoutManager();
	
public:

	virtual bool InjectTouchDown(const rTouch& touch);
	virtual bool InjectTouchMove(const rTouch& touch);
	virtual bool InjectTouchUp(const rTouch& touch);

	virtual bool InjectMouseDownEvent(rMouseButton button, const rMouseState& mouse);
	virtual bool InjectMouseUpEvent(rMouseButton button, const rMouseState& mouse);
	virtual bool InjectMouseMotionEvent(const rMouseState& mouse);
	virtual bool InjectMouseWheelEvent(rMouseWheelDirection direction, const rMouseState& mouse);
	
	void Update(rEngine& engine);
	void Draw(rEngine& engine);

	void Clear();

	ruiOverlay* CreateOverlay(rViewport* viewport);

private:
	rViewport* DetermineViewport(const rPoint& point);

	

private:
	ruiViewportOverlayMap m_overlays;

};

#endif
