#ifndef RUI_ANALOGSTICK_HPP
#define RUI_ANALOGSTICK_HPP

#include "rBuild.hpp"

#include "ui/ruiWidget.hpp"
#include "input/rController.hpp"
#include "rMathUtil.hpp"

#include "rEngine.hpp"

#include "rCircle2.hpp"
#include "rLog.hpp"

class RECONDITE_API ruiAnalogStick : public ruiWidget{
public:

	ruiAnalogStick(const rString& id, ruiIDocument* document, rEngine* engine);
	virtual void Draw();

	virtual rString GetWidgetType() const;

	void SetController(rController* controller, size_t stickIndex);
	virtual void SetPosition(int x, int y);
	virtual void SetPosition(const rPoint& position);

public:
	virtual bool OnPointerDown(const rPoint& position);
	virtual bool OnPointerMove(const rPoint& position);
	virtual bool OnPointerUp(const rPoint& position);

protected:
	virtual rSize ComputeSize();

private:
	void UpdateController();
	
	void UpdateStick(const rVector2& position);

private:
	size_t m_stickIndex;
	rController* m_controller;
	
	rSize m_indicatorSize;
	
	rCircle2 m_outerCircle;
	rCircle2 m_stick;
	
	bool m_dragging;
};

#endif
