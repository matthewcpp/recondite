#ifndef R_PINCHGESTURE_HPP
#define R_PINCHGESTURE_HPP

#include "rBuild.hpp"
#include "rString.hpp"

#include "input/riGesture.hpp"

class RECONDITE_API rPinchGesture : public riGesture{
public:
	rPinchGesture();
	
	virtual rString Name() const;
	virtual bool Active() const;
	virtual float Amount() const;
	virtual float PreviousAmount() const;
	virtual bool Position(size_t index, rPoint& position) const;
	virtual bool PreviousPosition(size_t index, rPoint& position) const;
	
	
	virtual void OnTouchDown(const rTouch& touch);
	virtual void OnTouchMove(const rTouch& touch);
	virtual void OnTouchUp(const rTouch& touch);
	
private:
	int m_touch1Id;
	int m_touch2Id;
	
	rPoint touch1Pos, touch1Prev;
	rPoint touch2Pos, touch2Prev;
};

#endif
