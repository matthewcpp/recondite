#ifndef R_OPENGLCONTENTMANAGER_HPP
#define R_OPENGLCONTENTMANAGER_HPP

#include "rBuild.hpp"

#include "rGraphicsDevice.hpp"
#include "rContentManager.hpp"

class RECONDITE_API rOpenGLContentManager : public rContentManager {
public:
	rOpenGLContentManager(rGraphicsDevice* graphicsDevice);

public:
	virtual void InitDefaultAssets();
};

#endif
