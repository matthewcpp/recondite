#ifndef RUI_LAYOUTMANAGER_HPP
#define RUI_LAYOUTMANAGER_HPP

#include <vector>

#include "rInput.hpp"
#include "rEngine.hpp"

#include "ui/ruiWidget.hpp"
typedef std::vector<ruiWidget*> rWidgetVector;

class ruiLayoutManager : public rInputListener {
	ruiLayoutManager();
	~ruiLayoutManager();
	
public:
	virtual void OnTouchEvent(const rTouch& touch);

	bool InjectTouchDown(const rTouch& touch);
	bool InjectTouchMove(const rTouch& touch);
	bool InjectTouchUp(const rTouch& touch);
	
	void Update(rEngine& engine);
	void Draw(rEngine& engine);
	
	void AddWidget(ruiWidget* widget);
	
	void Clear();
private:
	
	rWidgetVector m_widgets;
	ruiWidget* m_activeWidget;
};

#endif
