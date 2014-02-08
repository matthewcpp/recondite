#ifndef R_GESTURETRACKER_HPP
#define R_GESTURETRACKER_HPP

#include <map>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "input/riGesture.hpp"
#include "input/rPinchGesture.hpp"
#include "input/rDragGesture.hpp"

typedef std::map<rString, riGesture*> rGestureMap;


class rGestureTracker : public riGestureTracker{
public:
	rGestureTracker();
	
	void OnTouchDown(const rTouch& touch);
	void OnTouchMove(const rTouch& touch);
	void OnTouchUp(const rTouch& touch);
	
	void TrackGesture(const rString& name, riGesture* gesture);
	void DeleteGesture(const rString& name);
	
	virtual size_t TrackedGestureCount() const;
	virtual riGesture* GetGesture(const rString& name) const;
	virtual float Amount(const rString& gestureName) const;
	virtual float AmountDelta(const rString& gestureName) const;
	virtual rPoint Position(const rString& gestureName, size_t index) const;
	virtual rPoint PositionDelta(const rString& gestureName, size_t index) const;
	virtual float Active(const rString& gestureName) const;
		
private:
	
	rGestureMap m_gestures;
};

#endif
