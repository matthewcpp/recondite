#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>

#include "rModuleLoader.hpp"

rModule* rModuleLoader::LoadModule(const rString& path){
	rLog::Info("Loading module: %s", path.c_str());

	HMODULE module = LoadLibrary(path.c_str());

	if (module == NULL){
		rLog::Error("Error loading module: unable to open module");
		return NULL;
	}

	m_moduleLoadFunc = (rModuleLoadFunction) GetProcAddress(module, "CreateModule");

	if (m_moduleLoadFunc == NULL){
		rLog::Error("Error loading module: CreateModule method not found in shared library");
		return NULL;
	}

	m_moduleUnloadFunc = (rModuleUnloadFunction) GetProcAddress(module, "DeleteModule");

	if (m_moduleLoadFunc == NULL){
		rLog::Error("Error loading module: DeleteModule method not found in shared library");
		return NULL;
	}
	
	return (this->m_moduleLoadFunc)();
}

void rModuleLoader::UnloadModule(rModule* module){
	return (this->m_moduleUnloadFunc)(module);
}