#ifndef R_INPUTMANAGER_HPP
#define R_INPUTMANAGER_HPP

#include <map>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rTouch.hpp"

typedef std::map<unsigned int , rTouch*> rTouchMap;

class rInputManager {
public:
	unsigned int CreateTouch(const rPoint& position);
	rTouch* GetTouch(unsigned int id);
	void UpdateTouch(unsigned int id, rTouchType type, const rPoint& position);
	
private:
	unsigned int m_nextTouchId;
};

#endif