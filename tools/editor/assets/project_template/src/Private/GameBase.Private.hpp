#pragma once

#include "rModule.hpp"

class GameBase : public recondite::Module{
public:
	virtual void Register(rEngine* engine) final;
};