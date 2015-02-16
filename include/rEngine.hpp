#ifndef R_ENGINE_HPP
#define R_ENGINE_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rRenderer.hpp"
#include "rContentManager.hpp"
#include "rTime.hpp"
#include "rInput.hpp"
#include "rActorFactory.hpp"

#include "interface/riComponent.hpp"
#include "interface/riScene.hpp"
#include "ui/ruiInterface.hpp"

class rEngine{
public:
	rContentManager* content;
	rActorFactory* actors;
	rRenderer* renderer;
	rInput* input;
	rTime time;
	riComponent* component;
	riScene* scene;
	ruiIManager* ui;
};

#endif
