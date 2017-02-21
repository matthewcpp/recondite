#ifndef R_ENGINE_HPP
#define R_ENGINE_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rRenderer.hpp"
#include "rContentManager.hpp"
#include "rTime.hpp"
#include "rInput.hpp"
#include "rActorFactory.hpp"
#include "rViewportManager.hpp"
#include "rBehaviorManager.hpp"
#include "rResourceManager.hpp"

#include "interface/riScene.hpp"

class ruiIManager;
class rInputManager;

class rEngine{
public:
	rEngine(rGraphicsDevice* graphicsEngine, rContentManager* contentManager, rInputManager* inputManager, 
		rFileSystem* fileSystem, recondite::ResourceManager* resourceManager);

public:
	rContentManager* content;
	rActorFactory* actors;
	rRenderer* renderer;
	rInput* input;
	rTime time;
	riScene* scene;
	ruiIManager* ui;
	recondite::ViewportManager* viewports;
	recondite::BehaviorManager* behaviors;
	rFileSystem* filesystem;
	recondite::ResourceManager* resources;

private:
	rGraphicsDevice* _graphicsEngine;
};

#endif
