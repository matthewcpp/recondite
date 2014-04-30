#ifndef R_MODULELOADER_HPP
#define R_MODULELOADER_HPP

#include "rBuild.hpp"

#include "rLog.hpp"

#include "rString.hpp"
#include "rModule.hpp"

class RECONDITE_API rModuleLoader{
public:
	rModule* LoadModule(const rString& path);
	void UnloadModule(rModule* module);

private:
	typedef rModule* (*rModuleLoadFunction)();
	typedef void (*rModuleUnloadFunction)(rModule*);

private:
	rModuleLoadFunction m_moduleLoadFunc;
	rModuleUnloadFunction m_moduleUnloadFunc;
	
};

#endif