#include "rComponent.hpp"
#include "asset/rAssetManifest.hpp"

#include "xml/rXMLDocument.hpp"
#include "xml/rXMLSerialization.hpp"

rComponent::rComponent(){
	m_isReady = false;

	m_scene = new rScene(&m_engine);
	m_engine.actors = &m_actorFactory;
	m_engine.scene = m_scene;
	m_activeViewport = nullptr;

	InitDefaultActorClasses();
}

bool rComponent::Init(){
	Log::Init();

	return true;
}

void rComponent::Uninit(){
	Log::Shutdown();
}

void rComponent::LoadScene(const rString& name){
	auto assetStream = m_engine.content->FileSystem()->GetReadFileRef(name + ".assets");
	if (assetStream) {
		recondite::AssetManifest assetManifest;
		int error = assetManifest.Read(*assetStream);
		if (!error) {
			m_engine.content->LoadFromManifest(assetManifest);
		}
	}

	auto levelStream = m_engine.content->FileSystem()->GetReadFileRef(name);

	if (levelStream){
		rXMLDocument doc;
		doc.LoadFromStream(*levelStream);

		rXMLElement* element = doc.GetRoot();
		rXMLSerializationSource* source = new rXMLSerializationSource(element);
		m_scene->Load(source);
		delete source;
	}
}

bool rComponent::SaveScene(const rString& path){
	return SaveSceneXML(path);
}

void rComponent::ClearScene(){
	m_scene->Clear();
}

bool rComponent::SaveSceneXML(const rString& path){
	rXMLDocument doc;
	rXMLElement* element = doc.CreateRoot("level");

	riSerializationTarget* target = new rXMLSerializationTarget(element);
	m_scene->Save(target);

	rOFileStream fileStream(path);
	doc.WriteToStream(fileStream);
	delete target;

	return true;
}

void rComponent::InitEngine(rGraphicsDevice* graphics, rContentManager* content, rInputManager* input, rFileSystem* fileSystem){
	m_graphicsDevice = graphics;

	m_uiManager = new ruiManager(&m_engine);
	input->SetUIManager(m_uiManager);
	m_engine.ui = m_uiManager;

	m_engine.component = this;

	m_engine.content = content;
	m_engine.input = input;
	m_engine.renderer = new rRenderer(graphics, content);
	m_engine.time.Start(GetTimeMiliseconds());

	m_engine.scene = m_scene;

	m_fileSystem = fileSystem;

	m_isReady = true;
}

bool rComponent::LoadDefaultResources() {
	m_graphicsDevice->Init();

	rString defaultAssetPath = GetBasePath() + "default/";
	return m_engine.content->InitDefaultAssets(defaultAssetPath);
}

rViewport* rComponent::CreateViewport(const rString& name){
	if (m_viewports.count(name)){
		return NULL;
	}
	else {
		rViewport* viewport = new rViewport(name);
		m_viewports[name] = viewport;

		viewport->SetPosition(0, 0);
		viewport->SetSize(DisplaySize());

		return viewport;
	}
}

rViewport* rComponent::GetViewport(const rString& name) const{
	rViewportMap::const_iterator it = m_viewports.find(name);

	if (it != m_viewports.end()){
		return it->second;
	}
	else{
		return NULL;
	}
}

void rComponent::GetViewportNames(rArrayString& names) const{
	for (auto& entry : m_viewports){
		names.push_back(entry.first);
	}
}

void rComponent::DeleteViewport(const rString& name){
	auto it = m_viewports.find(name);

	if (it != m_viewports.end()){
		delete it->second;
		m_viewports.erase(it);
	}
}

void rComponent::SetActiveViewport(rViewport* viewport) {
	m_activeViewport = viewport;
}

rViewport* rComponent::GetActiveViewport() {
	return m_activeViewport;
}

size_t rComponent::NumViewports() const{
	return m_viewports.size();
}

bool rComponent::IsReady() const{
	return m_isReady;
}

rEngine* rComponent::GetEngine(){
	return &m_engine;
}

rScene* rComponent::GetScene(){
	return m_scene;
}

void rComponent::AddActorClass(const rString& name, rActorFactory::ActorFunction func){
	m_actorFactory.AddActorClass(name, func);
}

//TODO: find a better place to put this?
#include "primitive/rPrimitiveBox.hpp"
#include "primitive/rPrimitiveGrid.hpp"
#include "primitive/rPrimitiveCone.hpp"
#include "primitive/rPrimitiveCylinder.hpp"
#include "primitive/rPrimitiveSphere.hpp"
#include "rProp.hpp"

void rComponent::InitDefaultActorClasses(){
	m_actorFactory.AddActorClass("PrimitiveBox",
		[](rEngine* engine, const rString& id)->rActor3*{
		return new rPrimitiveBox(id, engine);
	});

	m_actorFactory.AddActorClass("PrimitiveGrid",
		[](rEngine* engine, const rString& id)->rActor3*{
		return new rPrimitiveGrid(id, engine);
	});

	m_actorFactory.AddActorClass("PrimitiveCone",
		[](rEngine* engine, const rString& id)->rActor3*{
		return new rPrimitiveCone(id, engine);
	});

	m_actorFactory.AddActorClass("PrimitiveCylinder",
		[](rEngine* engine, const rString& id)->rActor3*{
		return new rPrimitiveCylinder(id, engine);
	});

	m_actorFactory.AddActorClass("PrimitiveSphere",
		[](rEngine* engine, const rString& id)->rActor3*{
		return new rPrimitiveSphere(id, engine);
	});

	m_actorFactory.AddActorClass("Prop",
		[](rEngine* engine, const rString& id)->rActor3* {
		return new rProp(id, engine);
	});
}