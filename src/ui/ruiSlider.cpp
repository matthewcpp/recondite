#include "ui/ruiSlider.hpp"

#include "rLog.hpp"

ruiSlider::ruiSlider(const rString& id, ruiIDocument* document, rEngine* engine)
	:ruiWidget(id, document, engine)
{
	m_value = 0.0f;
	m_minValue = 0.0f;
	m_maxValue = 1.0f;

	m_handleSize.Set(10, 25);
	m_trackSize.Set(125, 10);
	m_handlePosition = 0.0;
	
	handleGrabbed = false;
}

float ruiSlider::GetValue() const{
	return m_value;
}

bool ruiSlider::SetValueRange(float min, float max){
	if (min > max){
		return false;
	}
	else{
		m_minValue = min;
		m_maxValue = max;

		m_value = std::max<float>(m_value, m_minValue);
		m_value = std::min<float>(m_value, m_maxValue);

		m_handlePosition = m_value / (m_maxValue - m_minValue);

		return true;
	}
}

float ruiSlider::GetMinValue(){
	return m_minValue;
}

float ruiSlider::GetMaxValue(){
	return m_maxValue;
}

void ruiSlider::SetValue(float value){
	value = rMath::Clamp<float>(value, m_minValue , m_maxValue);

	if (value != m_value){
		m_value = value;
		m_handlePosition = m_value / (m_maxValue - m_minValue);

		ruiWidgetEvent event(this);
		Trigger(ruiEVENT_SLIDER_CHANGE, event);
	}
}

void ruiSlider::SetHandleSize(const rSize& size){
	m_handleSize = size;
	InvalidateSize();
}

void ruiSlider::SetHandleSize(int width, int height){
	m_handleSize.Set(width, height);
	InvalidateSize();
}

rSize ruiSlider::GetHandleSize() const{
	return m_handleSize;
}

void ruiSlider::SetTrackSize(const rSize& size){
	m_trackSize = size;
	InvalidateSize();
}

void ruiSlider::SetTrackSize(int width, int height){
	m_trackSize.Set(width, height);
	InvalidateSize();
}

rSize ruiSlider::GeTrackSize() const{
	return m_trackSize;
}

rRect ruiSlider::HandleRect(){
	rRect trackRect = TrackRect();
	return HandleRect(trackRect);
}

rRect ruiSlider::HandleRect(const rRect& trackRect){
	rPoint point(trackRect.x + int(trackRect.width * m_handlePosition), trackRect.y + (trackRect.height / 2));
	point.x -= m_handleSize.x / 2;
	point.y -= m_handleSize.y / 2;

	return rRect(point, m_handleSize);
}

rRect ruiSlider::TrackRect(){
	rPoint contentPosition = ContentPosition();
	rSize computedSize = ComputeSize();
	contentPosition.y += (computedSize.y - m_trackSize.y) / 2;
	contentPosition.x += m_handleSize.x / 2;

	return rRect(contentPosition, m_trackSize);
}


bool ruiSlider::OnPointerDown(const rPoint& position){
	rRect trackRect = TrackRect();
	rRect handleRect = HandleRect(trackRect);

	if (handleRect.ContainsPoint(position)){
		StartDrag(position);
		return true;
	}
	else if (trackRect.ContainsPoint(position)){
		HandleTrackClick(trackRect, position);
		return true;
	}

	return false;
}

void ruiSlider::HandleTrackClick(const rRect& trackRect, const rPoint& position){
	float newPosition = float(position.x - trackRect.Left() ) / ((float)trackRect.Right() - (float)trackRect.Left());
	UpdateValueFromHandlePosition(newPosition);
}

void ruiSlider::UpdateValueFromHandlePosition(float position){
	m_handlePosition = position;
	m_value = m_minValue + m_handlePosition * (m_maxValue - m_minValue);

	ruiWidgetEvent event(this);
	Trigger(ruiEVENT_SLIDER_CHANGE, event);
}

bool ruiSlider::OnPointerUp(const rPoint& position){
	if (handleGrabbed){
		handleGrabbed = false;

		ruiWidgetEvent event(this);
		Trigger(ruiEVENT_SLIDER_DRAG_END, event);
		return true;
	}
	else{
		return false;
	}
}

bool ruiSlider::OnPointerMove(const rPoint& position){
	if (handleGrabbed){
		rRect trackRect= TrackRect();
		rPoint delta = position - m_prevDragPos;
		float deltaAmount = (float)delta.x / (float)m_trackSize.x;
		float newPosition = rMath::Clamp<float>(m_handlePosition + deltaAmount, 0.0f, 1.0f);

		UpdateValueFromHandlePosition(newPosition);
		m_prevDragPos = position;

		ruiWidgetEvent event(this);
		Trigger(ruiEVENT_SLIDER_DRAG_MOVE, event);

		return true;
	}
	else{
		return false;
	}
}

void ruiSlider::StartDrag(const rPoint& position){
	handleGrabbed = true;
	m_prevDragPos = position;

	ruiWidgetEvent event(this);
	Trigger(ruiEVENT_SLIDER_DRAG_BEGIN, event);
}

rSize ruiSlider::ComputeSize(){
	rSize contentSize(std::max<int>(m_trackSize.x, m_handleSize.x), std::max<int>(m_trackSize.y, m_handleSize.y));

	//add in space for handles when at the extreme of the track
	contentSize.x += m_handleSize.x;

	return contentSize;
}

void ruiSlider::Draw(){
	rRect track = TrackRect();
	rRect handle = HandleRect(track);
	ruiStyle* style = ComputedStyle();
	
	rColor color(51,102,255,255);
	style->GetColor("background-color", color);
	m_engine->renderer->SpriteBatch()->RenderRectangle(track, color);

	color.Set(255,255,255,255);
	style->GetColor("color", color);
	m_engine->renderer->SpriteBatch()->RenderRectangle(handle, color, 0.01);
}

rString ruiSlider::GetWidgetType() const{
	return "slider";
}