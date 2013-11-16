#ifndef RUI_SLIDER_HPP
#define RUI_SLIDER_HPP

#include <cmath>

#include "rTypes.hpp"
#include "rDefs.hpp"
#include "rMathUtil.hpp"

#include "ui/ruiWidget.hpp"
#include "ui/ruiEventType.hpp"

class ruiSlider : public ruiWidget{
public:
	ruiSlider(int id, const rPoint& position, const rSize& size);
	
public:
	
	int GetValue() const;
	void SetValue(int value);
	
	void SetHandleSize(int size);
	int GetHandleSize() const;
	
	rRect HandleRect() const;
	
	virtual void Draw(rEngine& engine);
	
	virtual void OnTouchDown(const rTouch& touch);
	virtual void OnTouchMove(const rTouch& touch);

private:
	void StartDrag(const rPoint& position);
	void HandleDrag(const rPoint& position);
	
private:
	int m_value;
	int m_handleSize;
	
	rPoint m_prevDrag;
	
	bool handleGrabbed;
};

#endif