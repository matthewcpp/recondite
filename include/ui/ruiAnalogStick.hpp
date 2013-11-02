#ifndef RUI_ANALOGSTICK_HPP
#define RUI_ANALOGSTICK_HPP

#include "ui/ruiWidget.hpp"
#include "input/rController.hpp"
#include "rMathUtil.hpp"

#include "rEngine.hpp"

#include "rCircle2.hpp"
#include "rLog.hpp"

class ruiAnalogStick : public ruiWidget{
public:

	ruiAnalogStick(rController* controller, size_t stickIndex, int id, const rPoint& position, const rSize& size);
	
	virtual void Update(rEngine& engine);
	virtual void Draw(rEngine& engine);
	
private:

	void SetCircles();
	int UpdateTouch(rEngine& engine);
	void UpdateTouchIndicator(rEngine& engine);
	void UpdateController();
	
private:
	size_t m_stickIndex;
	rController* m_controller;
	
	rSize m_indicatorSize;
	
	rCircle2 m_outerCircle;
	rCircle2 m_touchIndicator;
	
	int m_touchId;
};

#endif
