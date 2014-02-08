#ifndef R_OPENGLCONTENTMANAGER_HPP
#define R_OPENGLCONTENTMANAGER_HPP

#include "rContentManager.hpp"

class rOpenGLContentManager : public rContentManager {
public:
	rOpenGLContentManager(rGraphicsDevice* graphicsDevice);

public:
	virtual void InitDefaultAssets();
};

#endif
