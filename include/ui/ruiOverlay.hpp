#ifndef RUI_OVERLAY_HPP
#define RUI_OVERLAY_HPP

#include <vector>

#include "rBuild.hpp"

#include "rEngine.hpp"

#include "ruiBase.hpp"
#include "ruiWidget.hpp"



class RECONDITE_API ruiOverlay : public ruiIOverlay{
public:
	ruiOverlay();

public:
	virtual void AddWidget(ruiWidget* widget);
	ruiWidget* GetWidget(const rString& id);

	virtual void ShowModal(ruiWidget* widget);
	virtual void EndModal(ruiWidget* widget);

	void Update(rEngine& engine);
	void Draw(rEngine& engine);

	void Clear();

	void ActivateWidget(ruiWidget* widget);

	virtual bool InjectTouchDown(const rTouch& touch);
	virtual bool InjectTouchMove(const rTouch& touch);
	virtual bool InjectTouchUp(const rTouch& touch);

	virtual bool InjectMouseDownEvent(rMouseButton button, const rMouseState& mouse);
	virtual bool InjectMouseUpEvent(rMouseButton button, const rMouseState& mouse);
	virtual bool InjectMouseMotionEvent(const rMouseState& mouse);
	virtual bool InjectMouseWheelEvent(rMouseWheelDirection direction, const rMouseState& mouse);

	virtual bool InjectKeyDownEvent(rKey key, rKeyboardState& state);
	virtual bool InjectKeyUpEvent(rKey key, rKeyboardState& state);

	ruiWidget* SelectWidget(const rPoint& position);

protected:
	typedef std::vector<ruiWidget*> rWidgetVector;

private:

	rWidgetVector m_widgets;

	ruiWidget* m_activeWidget;
	ruiWidget* m_modalWidget;
};

#endif