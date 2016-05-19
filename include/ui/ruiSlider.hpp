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
	
	int GetValue() const;
	void SetValue(int value);
	
	void SetHandleSize(int size);
	int GetHandleSize() const;
	
	rRect HandleRect();
	
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
	void HandleDrag(const rPoint& position);
	
private:
	int m_value;
	int m_handleSize;
	
	rPoint m_prevDrag;
	
	bool handleGrabbed;
};

#endif
