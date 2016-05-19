#ifndef RUI_WIDGET_HPP
#define RUI_WIDGET_HPP

#include "rBuild.hpp"

#include "rRenderer.hpp"
#include "rSize.hpp"
#include "rPoint.hpp"

#include "ruiStyle.hpp"

#include "rEngine.hpp"

#include "ui/ruiDocument.hpp"
#include "ui/ruiStyleManager.hpp"
#include "ui/ruiWidgetBase.hpp"

#include "ui/ruiDefaultEventHandler.hpp"


class RECONDITE_API ruiWidget : public ruiWidgetBase, public ruiDefaultEventHandler {
public:
	ruiWidget(const rString& id, ruiDocument* document, rEngine* engine);

	virtual rRect BoundingBox();

	virtual rPoint Position() const;
	void SetPosition(int x, int y);
	void SetPosition(const rPoint& position);

protected:
	rPoint ContentPosition();
	rPoint m_position;
};

#endif
