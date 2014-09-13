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

	ruiAnalogStick(rController* controller, size_t stickIndex, const rString& id, rEngine* engine, const rPoint& position, const rSize& size);
	virtual void Draw(rEngine& engine);

	virtual rString GetWidgetType() const;

public:
	virtual void OnTouchDown(const rTouch& touch);
	virtual void OnTouchMove(const rTouch& touch);
	virtual void OnTouchUp(const rTouch& touch);

private:
	void SetCircles();
	void UpdateController();
	
	void UpdateStick(const rVector2& position);

private:
	size_t m_stickIndex;
	rController* m_controller;
	
	rSize m_indicatorSize;
	
	rCircle2 m_outerCircle;
	rCircle2 m_stick;
	
	int m_touchId;
};

#endif
