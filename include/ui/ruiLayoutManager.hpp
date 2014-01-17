#ifndef RUI_LAYOUTMANAGER_HPP
#define RUI_LAYOUTMANAGER_HPP

#include <vector>

#include "rInput.hpp"
#include "rEngine.hpp"

#include "ui/ruiBase.hpp"

#include "ui/ruiWidget.hpp"
typedef std::vector<ruiWidget*> rWidgetVector;

class ruiLayoutManager : public ruiInput, public ruiIWidgetManager, public ruiOverlay {
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
	
	void Update(rEngine& engine);
	void Draw(rEngine& engine);
	
	virtual void AddWidget(ruiWidget* widget);
	ruiWidget* GetWidget(int id);
	
	virtual rContentError LoadOverlay(const rString& path);

	virtual void ShowModal(ruiWidget* widget);
	virtual void EndModal(ruiWidget* widget);

	void Clear();

private:

	ruiWidget* SelectWidget(const rPoint& position);

private:
	
	rWidgetVector m_widgets;
	ruiWidget* m_activeWidget;
	ruiWidget* m_modalWidget;
};

#endif
