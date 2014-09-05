#ifndef RUI_SLIDER_HPP
#define RUI_SLIDER_HPP

#include "rBuild.hpp"
#include "rMathUtil.hpp"

#include "ui/ruiWidget.hpp"
#include "ui/ruiEvents.hpp"

class RECONDITE_API ruiSlider : public ruiWidget{
public:
	ruiSlider(const rString& id, rEngine* engine, const rPoint& position, const rSize& size);
	
public:
	
	int GetValue() const;
	void SetValue(int value);
	
	void SetHandleSize(int size);
	int GetHandleSize() const;
	
	rRect HandleRect() const;
	
	virtual void Draw(rEngine& engine);
	
public:

	void OnMouseDown(rEvent& event);
	void OnMouseMove(rEvent& event);
	void OnMouseUp(rEvent& event);

	void OnPointerDown(const rPoint& position);
	void OnPointerMove(const rPoint& position);
	void OnPointerUp(const rPoint& position);

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
