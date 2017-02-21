#include "rEngine.hpp"

#include "ui/ruiManager.hpp"
#include "rScene.hpp"
#include "rInputManager.hpp"

rEngine::rEngine(rGraphicsDevice* graphicsEngine, rContentManager* contentManager, rInputManager* inputManager, 
	rFileSystem* fileSystem, recondite::ResourceManager* resourceManager) {
	_graphicsEngine = graphicsEngine;
	filesystem = fileSystem;

	ruiManager* uiManager = new ruiManager(this);

	content = contentManager;
	actors = new rActorFactory();
	renderer = new rRenderer(_graphicsEngine, content);
	input = inputManager;
	scene = new rScene(this);
	ui = uiManager;
	inputManager->SetUIManager(uiManager);
	viewports = new recondite::ViewportManager();
	behaviors = new recondite::BehaviorManager();
	resources = resourceManager;
}