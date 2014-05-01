#include "ModelViewerPlugin.hpp"

rModule* CreateModule(){
	return new rDemoModule();
}

void DeleteModule(rModule* module){
}