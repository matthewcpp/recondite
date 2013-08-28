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
	rTouch(unsigned int id, const rPoint& pos, rTouchType type = rTOUCH_DOWN);
	rTouch(unsigned int id, int posX, int posY, rTouchType type = rTOUCH_DOWN);
	
	unsigned int Id() const;
	
	void Update(const rPoint& pos, rTouchType type);
	void Update(int posX, int posY, rTouchType type);
	
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
