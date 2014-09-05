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
#include "ui/ruiStyledWidgetBase.hpp"

#include "rEventHandler.hpp"


class RECONDITE_API ruiWidget : public ruiStyledWidgetBase, public rEventHandler {
public:
	ruiWidget(const rString& id, rEngine* engine);
	ruiWidget(const rString& id, rEngine* engine, const rPoint& position, const rSize& size);

	virtual void Draw(rEngine& engine) = 0;
	virtual void Update(rEngine& engine) {}
	virtual rRect BoundingBox() const;

	virtual rSize Size() const;
	void SetSize(int x, int y);

	virtual rPoint Position() const;
	void SetPosition(int x, int y);

protected:
	static void ShowModal(ruiWidget* widget);
	static void EndModal(ruiWidget* widget);

protected:
	rSize m_size;
	rPoint m_position;
};

#endif
