#ifndef BASICSCENEPLUGIN_HPP
#define BASICSCENEPLUGIN_HPP

#include "rModule.hpp"

#include "BasicSceneModule.hpp"

extern "C"{
	RECONDITE_MODULE_INTERFACE rModule* CreateModule();
	RECONDITE_MODULE_INTERFACE void DeleteModule(rModule* module);
}

#endif