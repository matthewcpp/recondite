#include "sdl/rSDLApplication.hpp"

rApplication::rApplication()
	:rApplicationBase()
{}

rApplication::~rApplication(){
}

bool rApplication::Init(){
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

void rApplication::Uninit(){
	rApplicationBase::Uninit();

	SDL_Quit();
}

void rApplication::ProcessEvent(SDL_Event& event){
	if (event.type == SDL_QUIT)
		m_isReady = false;

	m_inputManager->ProcessInputEvent(event);
}

unsigned long rApplication::GetTimeMiliseconds() const{
	return SDL_GetTicks();
}