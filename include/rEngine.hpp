#ifndef R_ENGINE_HPP
#define R_ENGINE_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rRenderer.hpp"
#include "rContentManager.hpp"
#include "rTime.hpp"
#include "rInput.hpp"

class rEngine{
public:
	rContentManager* content;
	rRenderer* renderer;
	rInput* input;
	rTime time;
};

#endif