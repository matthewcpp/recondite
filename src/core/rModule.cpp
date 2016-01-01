#include "rModule.hpp"

rModule::rModule(const rString& name) {
	m_moduleName = name;
}

rString rModule::GetModuleName() const {
	return m_moduleName;
}