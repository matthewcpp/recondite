#ifndef R_OPENGLCONTENTMANAGER_HPP
#define R_OPENGLCONTENTMANAGER_HPP

#include "rglBuild.hpp"

#include "rLog.hpp"

#include "rGraphicsDevice.hpp"
#include "rContentManager.hpp"
#include "rFileSystem.hpp"
#include "interface/riResourceManager.hpp"

using namespace recondite;

class RECONDITE_GL_API rOpenGLContentManager : public rContentManager {
public:
	rOpenGLContentManager(rGraphicsDevice* graphicsDevice, rFileSystem* fileSystem, iResourceManager* resourceManager);

public:
	virtual bool InitDefaultAssets(const rString& defaultAssetPath) override;
};

#endif
