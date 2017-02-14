#pragma once
#include <memory>

#include "Private/GameBase.Private.hpp"

class Game : public GameBase {
public:
	Game(rEngine* engine);

	virtual void AfterUpdateScene();

	virtual void Init(const rArrayString& args);
	virtual void Uninit();

	rEngine* _engine;
};