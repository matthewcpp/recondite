#ifndef RUI_SLIDER_HPP
#define RUI_SLIDER_HPP

#include "rBuild.hpp"
#include "rMathUtil.hpp"

#include "ui/ruiWidget.hpp"
#include "ui/ruiEvents.hpp"

class RECONDITE_API ruiSlider : public ruiWidget{
public:
	ruiSlider(const rString& id, ruiIDocument* document, rEngine* engine);
	
public:
	
	bool SetValueRange(float min, float max);
	float GetMinValue();
	float GetMaxValue();

	float GetValue() const;
	void SetValue(float value);
	
	void SetHandleSize(const rSize& size);
	void SetHandleSize(int width, int height);
	rSize GetHandleSize() const;

	void SetTrackSize(const rSize& size);
	void SetTrackSize(int width, int height);
	rSize GeTrackSize() const;
	
	rRect HandleRect();
	rRect HandleRect(const rRect& trackRect);
	rRect TrackRect();
	
	virtual void Draw();
	virtual rString GetWidgetType() const;

protected:
	virtual rSize ComputeSize();

public:
	bool OnPointerDown(const rPoint& position);
	bool OnPointerMove(const rPoint& position);
	bool OnPointerUp(const rPoint& position);

private:
	void StartDrag(const rPoint& position);
	void HandleTrackClick(const rRect& trackRect, const rPoint& position);
	void UpdateValueFromHandlePosition(float position);
	
private:
	float m_value;
	float m_minValue;
	float m_maxValue;

	rSize m_trackSize;
	rSize m_handleSize;
	float m_handlePosition;
	rPoint m_prevDragPos;
	
	bool handleGrabbed;
};

#endif
