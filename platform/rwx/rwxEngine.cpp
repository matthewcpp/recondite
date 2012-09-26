#include "rwxEngine.hpp"

rwxEngine::rwxEngine(){
	m_graphicsDevice = new rOpenGLGraphicsDevice();
	m_contentManager = new rwxContentManager(m_graphicsDevice);
}

rwxEngine::~rwxEngine(){
	Uninit();
	
	delete m_contentManager;
	delete m_graphicsDevice;
}

void rwxEngine::Uninit(){
	m_contentManager->UnloadAssets();
}

rGraphicsDevice* rwxEngine::GraphicsDevice(){
	return m_graphicsDevice;
}

rContentManager* rwxEngine::ContentManager(){
	return m_contentManager;
}