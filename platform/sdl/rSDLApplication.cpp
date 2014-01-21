#include "rSDLApplication.hpp"

rSDLApplication::rSDLApplication(rModule* module)
	:rApplication(module)
{}

rSDLApplication::~rSDLApplication(){
}

bool rSDLApplication::Init(){
	int width = 640;
	int height = 480;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) 
		return false;

	 if( SDL_SetVideoMode( width, height, 0, SDL_OPENGL  ) == 0 )
		 return false;

	 m_graphicsDevice = new rSDLGraphicsDevice();
	 m_contentManager = new rOpenGLContentManager(m_graphicsDevice);
	 m_inputManager = new rSDLInputManager();

	 InitEngine(m_graphicsDevice, m_contentManager, m_inputManager);

	 return true;
}

void rSDLApplication::Uninit(){
	m_module->Uninit(m_engine);

	SDL_Quit();
}

void rSDLApplication::ProcessEvent(SDL_Event& event){
	if (event.type == SDL_QUIT)
		m_isRunning = false;

	m_inputManager->ProcessInputEvent(event);
}

unsigned long rSDLApplication::GetTimeMiliseconds() const{
	return SDL_GetTicks();
}