#include "rEngine.hpp"

#include "ui/ruiManager.hpp"
#include "rScene.hpp"
#include "rInputManager.hpp"

#include "xml/rXMLSerialization.hpp"

#include "rPath.hpp"

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

	_levelBehavior = nullptr;
}

bool rEngine::LoadLevel(const rString& name) {
	rString levelPath = rPath::Assemble("levels", name, "rlvl");
	rString assetPath = levelPath + ".assets";

	auto assetStream = resources->Open(assetPath);
	auto levelStream = resources->Open(levelPath);

	if (assetStream) {
		recondite::AssetManifest assetManifest;
		int error = assetManifest.Read(*assetStream);
		if (!error) {
			content->LoadFromManifest(assetManifest);
		}
	}

	if (levelStream) {
		rXMLDocument doc;
		doc.LoadFromStream(*levelStream);

		rXMLElement* element = doc.GetRoot();
		rXMLSerializationSource* source = new rXMLSerializationSource(element);
		((rScene*)scene)->Load(source);
		delete source;
	}

	resources->Close(assetStream);
	resources->Close(levelStream);

	if (_levelBehavior) delete _levelBehavior;

	_levelBehavior = behaviors->CreateBehavior(name);
	if (_levelBehavior) {
		_levelBehavior->Init(this, name);
	}

	return true;
}