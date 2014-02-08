#ifndef RI_GESTURE_HPP
#define RI_GESTURE_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rPoint.hpp"
#include "input/rTouch.hpp"

class riGesture{
public:
	virtual rString Name() const = 0;
	virtual bool Active() const = 0;
	virtual float Amount() const = 0;
	virtual float PreviousAmount() const = 0;
	virtual bool Position(size_t index, rPoint& position) const = 0;
	virtual bool PreviousPosition(size_t index, rPoint& position) const = 0;
	
	
	virtual void OnTouchDown(const rTouch& touch) = 0;
	virtual void OnTouchMove(const rTouch& touch) = 0;
	virtual void OnTouchUp(const rTouch& touch) = 0;
};

class riGestureTracker{
public:
	virtual size_t TrackedGestureCount() const = 0;
	virtual riGesture* GetGesture(const rString& name) const = 0;
	virtual float Amount(const rString& gestureName) const = 0;
	virtual float AmountDelta(const rString& gestureName) const = 0;
	virtual rPoint PositionDelta(const rString& gestureName, size_t index) const = 0;
};

#endif