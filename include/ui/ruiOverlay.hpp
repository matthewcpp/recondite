#ifndef RUI_OVERLAY_HPP
#define RUI_OVERLAY_HPP

#include <vector>

#include "rBuild.hpp"

#include "rEngine.hpp"

#include "ui/ruiStyleManager.hpp"
#include "ui/ruiController.hpp"
#include "ruiEvents.hpp"

class ruiWidget;
class ruiLayout;

class RECONDITE_API ruiIDocument{
	virtual bool ShowContextMenu(ruiMenu* menu, ruiStyle* style, const rPoint& position, rEventHandler* handler) = 0;
	virtual void CancelContextMenu() = 0;
	virtual void AddWidget(ruiWidget* widget) = 0;
	virtual ruiWidget* GetWidget(const rString& id) = 0;
};

class RECONDITE_API ruiOverlay : public ruiIDocument{
public:
	ruiOverlay(rEngine* engine, rViewport* viewport);
	~ruiOverlay();

public:
	virtual bool ShowContextMenu(ruiMenu* menu, ruiStyle* style, const rPoint& position, rEventHandler* handler);
	virtual void CancelContextMenu();

public:
	void ProcessMouseDownEvent(ruiMouseEvent& event);
	void ProcessMouseMotionEvent(ruiMouseEvent& event);
	void ProcessMouseUpEvent(ruiMouseEvent& event);
	void ProcessMouseWheelEvent(ruiMouseEvent& event);

public:
	virtual void AddWidget(ruiWidget* widget);
	virtual ruiWidget* GetWidget(const rString& id);

	ruiController* GetController();
	void SetController(ruiController* controller);

	void Update();
	void Draw();

	void Clear();

	ruiWidget* SelectWidget(const rPoint& position);

	ruiStyleManager* Styles();

	ruiLayout* Layout() const;
	void SetLayout(ruiLayout* layout);

	void UpdateLayout(bool force = false);

	rString GetDefaultId () const;


private:
	struct Impl;
	Impl* _impl;
};

#endif