#include "rComponent.hpp"
#include "asset/rAssetManifest.hpp"

#include "xml/rXMLDocument.hpp"
#include "xml/rXMLSerialization.hpp"

rComponent::rComponent(){
	m_isReady = false;
}

bool rComponent::Init(){
	Log::Init();

	return true;
}

void rComponent::Uninit(){
	Log::Shutdown();
}

void rComponent::LoadScene(const rString& name){
	auto assetStream = m_engine->filesystem->OpenReadFileRef(name + ".assets");
	auto levelStream = m_engine->filesystem->OpenReadFileRef(name);

	if (assetStream) {
		recondite::AssetManifest assetManifest;
		int error = assetManifest.Read(*assetStream);
		if (!error) {
			m_engine->content->LoadFromManifest(assetManifest);
		}
	}

	if (levelStream){
		rXMLDocument doc;
		doc.LoadFromStream(*levelStream);

		rXMLElement* element = doc.GetRoot();
		rXMLSerializationSource* source = new rXMLSerializationSource(element);
		((rScene*)m_engine->scene)->Load(source);
		delete source;
	}

	m_engine->filesystem->CloseReadFileRef(assetStream);
	m_engine->filesystem->CloseReadFileRef(levelStream);
}

bool rComponent::SaveScene(const rString& path){
	return SaveSceneXML(path);
}

void rComponent::ClearScene(){
	((rScene*)m_engine->scene)->Clear();
}

bool rComponent::SaveSceneXML(const rString& path){
	rXMLDocument doc;
	rXMLElement* element = doc.CreateRoot("level");

	riSerializationTarget* target = new rXMLSerializationTarget(element);
	((rScene*)m_engine->scene)->Save(target);

	auto fileStream = m_engine->filesystem->OpenWriteFileRef(path);
	doc.WriteToStream(*fileStream);
	m_engine->filesystem->CloseWriteFileRef(fileStream);

	delete target;

	return true;
}

void rComponent::InitEngine(rGraphicsDevice* graphics, rContentManager* content, rInputManager* input, 
	rFileSystem* fileSystem, recondite::ResourceManager* resourceManager){
	m_engine = new rEngine(graphics, content, input, fileSystem, resourceManager);
	InitDefaultActorClasses();
	m_graphicsDevice = graphics;

	m_fileSystem = fileSystem;

	m_isReady = true;
}

bool rComponent::LoadDefaultResources() {
	m_graphicsDevice->Init();

	rString defaultAssetPath = GetBasePath() + "default/";
	return m_engine->content->InitDefaultAssets(defaultAssetPath);
}

bool rComponent::IsReady() const{
	return m_isReady;
}

rEngine* rComponent::GetEngine(){
	return m_engine;
}

rScene* rComponent::GetScene() {
	return (rScene*)m_engine->scene;
}

//TODO: find a better place to put this?
#include "primitive/rPrimitiveBox.hpp"
#include "primitive/rPrimitiveGrid.hpp"
#include "primitive/rPrimitiveCone.hpp"
#include "primitive/rPrimitiveCylinder.hpp"
#include "primitive/rPrimitiveSphere.hpp"
#include "rProp.hpp"

void rComponent::InitDefaultActorClasses(){
	m_engine->actors->AddActorClass("PrimitiveBox",
		[](rEngine* engine, const rString& id)->rActor3*{
		return new rPrimitiveBox(id, engine);
	});

	m_engine->actors->AddActorClass("PrimitiveGrid",
		[](rEngine* engine, const rString& id)->rActor3*{
		return new rPrimitiveGrid(id, engine);
	});

	m_engine->actors->AddActorClass("PrimitiveCone",
		[](rEngine* engine, const rString& id)->rActor3*{
		return new rPrimitiveCone(id, engine);
	});

	m_engine->actors->AddActorClass("PrimitiveCylinder",
		[](rEngine* engine, const rString& id)->rActor3*{
		return new rPrimitiveCylinder(id, engine);
	});

	m_engine->actors->AddActorClass("PrimitiveSphere",
		[](rEngine* engine, const rString& id)->rActor3*{
		return new rPrimitiveSphere(id, engine);
	});

	m_engine->actors->AddActorClass("Prop",
		[](rEngine* engine, const rString& id)->rActor3* {
		return new rProp(id, engine);
	});
}