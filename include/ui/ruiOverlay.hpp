#ifndef RUI_OVERLAY_HPP
#define RUI_OVERLAY_HPP

#include <vector>

#include "rBuild.hpp"

#include "rEngine.hpp"

#include "ui/ruiStyleManager.hpp"
#include "ui/ruiMenuManager.hpp"
#include "ui/ruiController.hpp"

class ruiWidget;
class ruiLayout;

class RECONDITE_API ruiOverlay {
public:
	ruiOverlay(rEngine* engine, rViewport* viewport);
	~ruiOverlay();

public:
	bool ShowContextMenu(ruiMenu* menu, const rPoint& position, rEventHandler* handler);
	bool ShowContextMenu(ruiMenu* menu, ruiStyle* style, const rPoint& position, rEventHandler* handler);
	void CancelContextMenu();

public:
	virtual void AddWidget(ruiWidget* widget);
	ruiWidget* GetWidget(const rString& id);

	ruiController* GetController();
	void SetController(ruiController* controller);

	void Update();
	void Draw();

	void Clear();

	void ActivateWidget(ruiWidget* widget);
	ruiWidget* ActiveWidget() const;

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