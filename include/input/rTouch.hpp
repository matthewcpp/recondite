#ifndef R_TOUCHEVENT_HPP
#define R_TOUCHEVENT_HPP

#include "rBuild.hpp"
#include "rString.hpp"

#include "rPoint.hpp"
#include "rVector2.hpp"

enum rTouchType{
	rTOUCH_DOWN,
	rTOUCH_MOVE,
	rTOUCH_UP,
	rTOUCH_CANCEL
};

class RECONDITE_API rTouch{
public:
	rTouch(int id, const rPoint& pos, rTouchType type = rTOUCH_DOWN);
	rTouch(int id, int posX, int posY, rTouchType type = rTOUCH_DOWN);
	
	int Id() const;
	
	void Update(const rPoint& pos, rTouchType type);
	void Update(int posX, int posY, rTouchType type);
	
	rPoint GetStartPosition() const;
	
	rPoint GetCurrentPosition() const;
	rVector2 GetCurrentPositionVector() const;
	
	rTouchType GetType() const;
private:
	rTouchType m_type;
	int m_id;
	
	rPoint m_startPosition;
	rPoint m_currentPosition;
};

#endif
