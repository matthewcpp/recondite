#include "sdl/rSDLApplication.hpp"

rApplication::rApplication()
	:rApplicationBase()
{
	m_window = nullptr;
}

rApplication::~rApplication(){
}

bool rApplication::Init(){
	int sdlInit = SDL_Init(SDL_INIT_VIDEO);

	char* base_path = SDL_GetBasePath();
	m_basePath = base_path;

	SDL_free(base_path);

	if (sdlInit < 0){
		rLog::Error("Error Initializing SDL: %i", sdlInit);
		return false;
	}

	m_window = SDL_CreateWindow("recondite",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1024, 768,
		SDL_WINDOW_OPENGL);

	if (m_window) {
		m_glContext = SDL_GL_CreateContext(m_window);
	}
	else {
		rLog::Error("Error Setting SDL OpenGL Video Mode.");
		return false;
	}

	if (!m_glContext){
		rLog::Error("Error Creating OpenGL context.");
		return false;
	}

	rFileSystem* fileSystem = new rFileSystem();
	 m_graphicsDevice = new rSDLGraphicsDevice(m_window);
	 m_contentManager = new rOpenGLContentManager(m_graphicsDevice, fileSystem);
	 m_inputManager = new rSDLInputManager();

	 InitEngine(m_graphicsDevice, m_contentManager, m_inputManager, fileSystem);
	 InitModule();

	 SDL_SetWindowTitle(m_window, m_module->GetModuleName().c_str());

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

rString rApplication::GetBasePath(){
	return m_basePath;
}