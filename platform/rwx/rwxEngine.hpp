#ifndef RWX_ENGINE_HPP
#define RWX_ENGINE_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rEngine.hpp"
#include "rgl/rOpenGLGraphicsDevice.hpp"
#include "rwxContentManager.hpp"

class rwxEngine : public rEngine{
public:
	rwxEngine();
	~rwxEngine();
	
	virtual rGraphicsDevice* GraphicsDevice();
	virtual rContentManager* ContentManager();

private:
	void Uninit();
	
private:	
	rOpenGLGraphicsDevice* m_graphicsDevice;
	rwxContentManager* m_contentManager;
};

#endif
