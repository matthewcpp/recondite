#ifndef R_INPUTMANAGER_HPP
#define R_INPUTMANAGER_HPP

#include <map>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rLog.hpp"

#include "rTouch.hpp"

typedef std::map<unsigned int , rTouch*> rTouchMap;

class rInputManager {
public:
	rTouch* CreateTouch(unsigned int id, const rPoint& position, rTouchType type = rTOUCH_DOWN);
	rTouch* GetTouch(unsigned int id);
	bool UpdateTouch(unsigned int id, const rPoint& position, rTouchType type);
	
	size_t TouchCount() const;
	void GetTouchIds(rIntArray& ids);
	
protected:
	void NotifyOfTouch(rTouch* touch);
	
protected:
	rTouchMap m_touches;
};

#endif
