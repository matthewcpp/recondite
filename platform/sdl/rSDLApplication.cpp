#include "rSDLApplication.hpp"

rSDLApplication::rSDLApplication()
	:rApplication()
{}

rSDLApplication::~rSDLApplication(){
}

bool rSDLApplication::Init(){
	int sdlInit = SDL_Init(SDL_INIT_VIDEO);

	if (sdlInit < 0){
		rLog::Error("Error Initializing SDL: %i", sdlInit);
		return false;
	}

	if (SDL_SetVideoMode(m_displaySize.x, m_displaySize.y, 0, SDL_OPENGL) == 0){
		rLog::Error("Error Setting SDL OpenGL Video Mode");
		return false;
	}

	 m_graphicsDevice = new rSDLGraphicsDevice();
	 m_contentManager = new rOpenGLContentManager(m_graphicsDevice);
	 m_inputManager = new rSDLInputManager();

	 InitEngine(m_graphicsDevice, m_contentManager, m_inputManager);
	 InitModule();

	 return true;
}

void rSDLApplication::Uninit(){
	rApplication::Uninit();

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