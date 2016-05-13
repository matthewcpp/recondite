#ifndef R_OPENGLCONTENTMANAGER_HPP
#define R_OPENGLCONTENTMANAGER_HPP

#include "rBuild.hpp"

#include "rLog.hpp"

#include "rGraphicsDevice.hpp"
#include "rContentManager.hpp"
#include "rFileSystem.hpp"

class RECONDITE_API rOpenGLContentManager : public rContentManager {
public:
	rOpenGLContentManager(rGraphicsDevice* graphicsDevice, rFileSystem* fileSystem);

public:
	virtual void InitDefaultAssets(const rString& defaultAssetPath);
};

#endif
