#ifndef RUI_DOCUMENT_HPP
#define RUI_DOCUMENT_HPP

#include <vector>
#include <functional>

#include "rBuild.hpp"

#include "rEngine.hpp"

#include "ui/ruiStyleManager.hpp"
#include "ui/ruiController.hpp"
#include "ruiEvents.hpp"

class ruiWidget;
class ruiLayout;

class RECONDITE_API ruiIDocument{
public:
	typedef std::function<void(void)> UpdateFunc;

	virtual bool ShowContextMenu(ruiMenu* menu, ruiStyle* style, const rPoint& position, rEventHandler* handler) = 0;
	virtual void CancelContextMenu() = 0;
	virtual void AddWidget(ruiWidget* widget) = 0;
	virtual ruiWidget* GetWidget(const rString& id) = 0;

	virtual uint32_t RunEveryUpdate(UpdateFunc func) = 0;
	virtual uint32_t RunNextUpdate(UpdateFunc func) = 0;

	virtual void ClearRunEveryUpdate(int handle) = 0;
	virtual void ClearNextUpdate(int handle) = 0;

	virtual ruiStyleManager* Styles() = 0;
};

class RECONDITE_API ruiDocument : public ruiIDocument{
public:
	ruiDocument(rEngine* engine, rViewport* viewport);
	~ruiDocument();

public:
	virtual bool ShowContextMenu(ruiMenu* menu, ruiStyle* style, const rPoint& position, rEventHandler* handler);
	virtual void CancelContextMenu();

	virtual uint32_t RunEveryUpdate(UpdateFunc func);
	virtual uint32_t RunNextUpdate(UpdateFunc func);
	virtual void ClearRunEveryUpdate(int handle);
	virtual void ClearNextUpdate(int handle);

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

	virtual ruiStyleManager* Styles();

	ruiLayout* Layout() const;
	void SetLayout(ruiLayout* layout);

	void UpdateLayout(bool force = false);

	rString GetDefaultId () const;


private:
	struct Impl;
	Impl* _impl;
};

#endif