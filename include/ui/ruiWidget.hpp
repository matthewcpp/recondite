#ifndef RUI_WIDGET_HPP
#define RUI_WIDGET_HPP

#include "rBuild.hpp"

#include "rRenderer.hpp"
#include "rSize.hpp"
#include "rPoint.hpp"

#include "ruiStyle.hpp"

#include "rEngine.hpp"

#include "ui/ruiBase.hpp"
#include "ui/ruiInterface.hpp"
#include "ui/ruiStyleManager.hpp"
#include "ui/ruiWidgetBase.hpp"

#include "rEventHandler.hpp"
#include "ui/ruiEvents.hpp"


class RECONDITE_API ruiWidget : public ruiWidgetBase, public rEventHandler {
public:
	ruiWidget(const rString& id, rEngine* engine);
	ruiWidget(const rString& id, rEngine* engine, const rPoint& position, const rSize& size);

	virtual rRect BoundingBox() const;

	virtual void Draw(rEngine& engine) = 0;

	virtual rSize Size() const;
	void SetSize(int x, int y);

	virtual rPoint Position() const;
	void SetPosition(int x, int y);

protected:
	virtual void OnPointerDown(const rPoint& position) {}
	virtual void OnPointerUp(const rPoint& position) {}
	virtual void OnPointerLeave(const rPoint& position) {}
	virtual void OnPointerEnter(const rPoint& position) {}

private:
	void BindDefaultEvents();

	void OnMouseDown(rEvent& event);
	void OnMouseUp(rEvent& event);
	void OnMouseLeave(rEvent& event);
	void OnMouseEnter(rEvent& event);

protected:
	rSize m_size;
	rPoint m_position;
};

#endif
