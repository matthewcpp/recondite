#ifndef R_DRAGGESTURE_HPP
#define R_DRAGGESTURE_HPP

#include "rBuild.hpp"
#include "rString.hpp"

#include "input/riGesture.hpp"

class RECONDITE_API rDragGesture : public riGesture{
public:
	rDragGesture();
	
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
	int m_touchId;
	
	rPoint m_position;
	rPoint m_prevPosition;
	rPoint m_startPosition;;
};

#endif