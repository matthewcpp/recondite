#ifndef R_SDLCONTENTMANAGER_HPP
#define R_SDLCONTENTMANAGER_HPP

#include "rContentManager.hpp"

class rSDLContentManager : public rContentManager {
public:
	rSDLContentManager(rGraphicsDevice* graphicsDevice);
public:
	void InitDefaultAssets();
};

#endif