#pragma once

#include "rModule.hpp"

class SelectionModule : public rModule {
public:
	SelectionModule(rEngine* engine);

public:
	virtual void Init(const rArrayString& args);
	virtual void LoadScene(const rString& sceneName) override;
	virtual void DeleteActor(rActor3* actor) override;

private:
	void CreatePrimitives();

private:
	rEngine* _engine;
};