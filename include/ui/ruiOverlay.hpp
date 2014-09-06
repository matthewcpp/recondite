#ifndef RUI_OVERLAY_HPP
#define RUI_OVERLAY_HPP

#include <vector>

#include "rBuild.hpp"

#include "rEngine.hpp"

#include "ui/ruiInterface.hpp"
#include "ruiWidget.hpp"

class RECONDITE_API ruiOverlay {
public:
	ruiOverlay();

public:
	virtual void AddWidget(ruiWidget* widget);
	ruiWidget* GetWidget(const rString& id);

	void Update(rEngine& engine);
	void Draw(rEngine& engine);

	void Clear();

	void ActivateWidget(ruiWidget* widget);
	ruiWidget* ActiveWidget() const;

	ruiWidget* SelectWidget(const rPoint& position);

protected:
	typedef std::vector<ruiWidget*> rWidgetVector;

private:

	rWidgetVector m_widgets;

	ruiWidget* m_activeWidget;
	ruiWidget* m_modalWidget;
};

#endif