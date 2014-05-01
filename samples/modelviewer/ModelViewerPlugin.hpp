#ifndef MODELVIEWERPLUGIN_HPP
#define MODELVIEWERPLUGIN_HPP

#include "rBuild.hpp"

#include "rModule.hpp"
#include "rDemoModule.hpp"

extern "C"{
	RECONDITE_API rModule* CreateModule();
	RECONDITE_API void DeleteModule(rModule* module);
}

#endif