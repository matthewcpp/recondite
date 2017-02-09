#pragma once

#include "rModule.hpp"

class SelectionModule : public recondite::Module {
public:
	SelectionModule(rEngine* engine);

public:
	virtual void Init(const rArrayString& args);

private:
	void CreatePrimitives();

private:
	rEngine* _engine;
};