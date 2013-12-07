#ifndef R_ENGINE_HPP
#define R_ENGINE_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rRenderer.hpp"
#include "interface/riContentManager.hpp"
#include "rTime.hpp"
#include "rInput.hpp"

class rEngine{
public:
	riContentManager* content;
	rRenderer* renderer;
	rInput* input;
	rTime time;
};

#endif
