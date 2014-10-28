#include "platform/rApplication.hpp"
#include "BasicSceneModule.hpp"

class rBasicSceneApplication : public rApplication{
public:
	virtual rModule* CreateModule(){
		return new BasicSceneModule();
	}
};

IMPLEMENT_MAIN(rBasicSceneApplication);