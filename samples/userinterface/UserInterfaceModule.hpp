#pragma once

#include "rModule.hpp"

class UserInterfaceModule : public recondite::Module{
public:
	UserInterfaceModule(rEngine* engine);

	virtual void Init(const rArrayString& args);

private:
	rEngine* _engine;
};