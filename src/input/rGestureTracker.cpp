#include "input/rGestureTracker.hpp"

rGestureTracker::rGestureTracker(){
	TrackGesture("pinch", new rPinchGesture());
	TrackGesture("drag", new rDragGesture());
}

void rGestureTracker::OnTouchDown(const rTouch& touch){
	for (rGestureMap::iterator it = m_gestures.begin(); it != m_gestures.end(); ++it)
		it->second->OnTouchDown(touch);
}

void rGestureTracker::OnTouchMove(const rTouch& touch){
	for (rGestureMap::iterator it = m_gestures.begin(); it != m_gestures.end(); ++it)
		it->second->OnTouchMove(touch);
}

void rGestureTracker::OnTouchUp(const rTouch& touch){
	for (rGestureMap::iterator it = m_gestures.begin(); it != m_gestures.end(); ++it)
		it->second->OnTouchUp(touch);
}

void rGestureTracker::TrackGesture(const rString& name, riGesture* gesture){
	if (m_gestures.count(name))
		delete m_gestures[name];
	
	m_gestures[name] = gesture;
}

void rGestureTracker::DeleteGesture(const rString& name){
	m_gestures.erase(name);
}

size_t rGestureTracker::TrackedGestureCount() const{
	return m_gestures.size();
}

riGesture* rGestureTracker::GetGesture(const rString& name) const{
	riGesture* gesture = NULL;
	
	rGestureMap::const_iterator it = m_gestures.find(name);
	if (it != m_gestures.end())
		gesture = it->second;

	return gesture;
}

float rGestureTracker::Amount(const rString& gestureName) const{
	riGesture* gesture = GetGesture(gestureName);
	
	if (gesture)
		return gesture->Amount();
	else
		return 0.0f;
}

float rGestureTracker::AmountDelta(const rString& gestureName) const{
	riGesture* gesture = GetGesture(gestureName);
	
	if (gesture)
		return gesture->Amount() - gesture->PreviousAmount();
	else
		return 0.0f;
}

rPoint rGestureTracker::PositionDelta(const rString& gestureName, size_t index) const{
	riGesture* gesture = GetGesture(gestureName);
	rPoint pos, prev;
	
	if (gesture && gesture->Position(index, pos) && gesture->PreviousPosition(index, prev))
		return pos - prev;
	else
		return rPoint::Zero;
}

rPoint rGestureTracker::Position(const rString& gestureName, size_t index) const{
	riGesture* gesture = GetGesture(gestureName);
	rPoint pos;

	if (gesture && gesture->Position(index, pos))
		return pos;
	else
		return rPoint::Zero;
}

float rGestureTracker::Active(const rString& gestureName) const{
	riGesture* gesture = GetGesture(gestureName);

	return (gesture && gesture->Active());
}
