#ifndef MODELVIEWERPLUGIN_HPP
#define MODELVIEWERPLUGIN_HPP

#include "rBuild.hpp"

#include "rModule.hpp"
#include "rDemoModule.hpp"

extern "C"{
	RECONDITE_MODULE_INTERFACE rModule* CreateModule();
	RECONDITE_MODULE_INTERFACE void DeleteModule(rModule* module);
}

#endif