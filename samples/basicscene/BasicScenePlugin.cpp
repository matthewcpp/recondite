#include "BasicScenePlugin.hpp"

rModule* CreateModule(){
	return new BasicSceneModule();
}

void DeleteModule(rModule* module){
	delete module;
}