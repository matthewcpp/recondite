#ifndef RUI_OVERLAY_HPP
#define RUI_OVERLAY_HPP

#include <vector>

#include "rBuild.hpp"

#include "rEngine.hpp"

#include "ui/ruiInterface.hpp"
#include "ui/ruiLayout.hpp"

#include "stream/rOStringStream.hpp"

#include "ruiWidget.hpp"

class RECONDITE_API ruiOverlay {
public:
	ruiOverlay(rViewport* viewport);

public:
	virtual void AddWidget(ruiWidget* widget);
	ruiWidget* GetWidget(const rString& id);

	void Update(rEngine& engine);
	void Draw(rEngine& engine);

	void Clear();

	void ActivateWidget(ruiWidget* widget);
	ruiWidget* ActiveWidget() const;

	ruiWidget* SelectWidget(const rPoint& position);

	ruiLayout* Layout() const;
	void SetLayout(ruiLayout* layout);

	void UpdateLayout(bool force = false);

	rString GetDefaultId () const;
protected:
	typedef std::vector<ruiWidget*> rWidgetVector;

private:

	rWidgetVector m_widgets;

	ruiWidget* m_activeWidget;
	ruiWidget* m_modalWidget;
	ruiLayout* m_layout;
	rViewport* m_viewport;
};

#endif