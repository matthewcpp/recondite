#include "rSDLApplication.hpp"

rSDLApplication::rSDLApplication(){
	
}

rSDLApplication::~rSDLApplication(){
}

bool rSDLApplication::Init(){
	int width = 640;
	int height = 480;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) 
		return false;

	 if( SDL_SetVideoMode( width, height, 0, SDL_OPENGL  ) == 0 )
		 return false;

	 m_isRunning = true;

	 m_graphicsDevice = new rSDLGraphicsDevice();
	 m_graphicsDevice->Init();

	 m_contentManager = new rSDLContentManager(m_graphicsDevice);
	 m_contentManager->InitDefaultAssets();

	 rFontData fontData;
	 fontData.LoadFromFile("assets/", "Consolas");
	 rFont* font = m_contentManager->LoadFont(fontData, "consolas");

	 m_engine.content = m_contentManager;
	 m_engine.renderer = new rRenderer(m_graphicsDevice, m_contentManager);

	 m_layoutManager = new ruiLayoutManager();
	 ruiPicker* picker = new ruiPicker(100, rPoint(25,10), rSize(250, 35));
	 picker->AddOption("item 1");
	 picker->AddOption("item 2");
	 m_layoutManager->AddWidget(picker);

	 TempInit();

	 m_engine.time.Start(GetTimeMiliseconds());

	 return true;
}

void rSDLApplication::Uninit(){
	SDL_Quit();
}

void rSDLApplication::Update(){
	m_layoutManager->Update(m_engine);
}

void rSDLApplication::Draw(){
	m_graphicsDevice->Clear();

	m_engine.renderer->Render(m_viewport);

	rAlignedBox3 box(-1,-1,-1, 1, 1, 1);

	m_engine.renderer->RenderWireBox(box, rColor::White);

	m_graphicsDevice->EnableDepthTesting(false);
	m_layoutManager->Draw(m_engine);

	m_graphicsDevice->SwapBuffers();

	m_frameCount++;
}

void rSDLApplication::ProcessEvent(SDL_Event& event){
	if (event.type == SDL_QUIT)
		m_isRunning = false;
}

unsigned long rSDLApplication::GetTimeMiliseconds() const{
	return SDL_GetTicks();
}

void rSDLApplication::TempInit(){
	m_camera = new rTargetCamera("camera", rVector3(0,0,5));
	m_camera->SetTarget(rVector3(0,0,-5));


	m_viewport.SetCamera(m_camera);
	m_viewport.SetClipping(1.0, 100.0f);
	m_viewport.SetSize(640,480);
	m_viewport.SetViewportType(rVIEWPORT_PERSP);
}