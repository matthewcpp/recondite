#ifndef RUI_LAYOUTMANAGER_HPP
#define RUI_LAYOUTMANAGER_HPP

#include <vector>

#include "rInput.hpp"
#include "rEngine.hpp"

#include "ui/ruiBase.hpp"

#include "ui/ruiWidget.hpp"
typedef std::vector<ruiWidget*> rWidgetVector;

class ruiLayoutManager : public rInputListener, public ruiIWidgetManager, public ruiOverlay {
public:
	ruiLayoutManager();
	~ruiLayoutManager();
	
public:
	virtual void OnTouchEvent(const rTouch& touch);

	bool InjectTouchDown(const rTouch& touch);
	bool InjectTouchMove(const rTouch& touch);
	bool InjectTouchUp(const rTouch& touch);
	
	void Update(rEngine& engine);
	void Draw(rEngine& engine);
	
	virtual void AddWidget(ruiWidget* widget);
	ruiWidget* GetWidget(int id);
	
	virtual rContentError LoadOverlay(const rString& path);

	virtual void ShowModal(ruiWidget* widget);
	virtual void EndModal(ruiWidget* widget);

	void Clear();
private:
	
	rWidgetVector m_widgets;
	ruiWidget* m_activeWidget;
	ruiWidget* m_modalWidget;
};

#endif
