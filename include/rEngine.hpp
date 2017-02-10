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

#include "interface/riScene.hpp"

class ruiIManager;
class rInputManager;

class rEngine{
public:
	rEngine(rGraphicsDevice* graphicsEngine, rContentManager* contentManager, rInputManager* inputManager, rFileSystem* fileSystem);

public:
	rContentManager* content;
	rActorFactory* actors;
	rRenderer* renderer;
	rInput* input;
	rTime time;
	riScene* scene;
	ruiIManager* ui;
	recondite::ViewportManager* viewports;

private:
	rGraphicsDevice* _graphicsEngine;
	rFileSystem* _fileSystem;
};

#endif
