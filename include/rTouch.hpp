#ifndef R_TOUCHEVENT_HPP
#define R_TOUCHEVENT_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rPoint.hpp"

enum rTouchType{
	rTOUCH_DOWN,
	rTOUCH_MOVE,
	rTOUCH_UP,
	rTOUCH_CANCEL
};

class rTouch{
public:
	rTouch(unsigned int id, rTouchType type, const rPoint& pos);
	rTouch(unsigned int id, rTouchType type, int posX, int posY);
	
	unsigned int Id() const;
	
	void Update(rTouchType type, const rPoint& pos);
	void Update(rTouchType type, int posX, int posY);
	
	rPoint GetStartPosition() const;
	
	rPoint GetCurrentPosition() const;
	
	rTouchType GetType() const;
private:
	rTouchType m_type;
	unsigned int m_id;
	
	rPoint m_startPosition;
	rPoint m_currentPosition;
};

#endif