#pragma once

#include "rBuild.hpp"

#include "rString.hpp"
#include "rEngine.hpp"

#include "rActor3.hpp"
#include "asset/rModel.hpp"

class RECONDITE_API rDrawable : public rActor3 {
public:
	rDrawable(const rString& id, rEngine* engine) : rActor3(id, engine), _model(nullptr) {}
	rDrawable(recondite::Model* model, const rString& id, rEngine* engine) : rActor3(id, engine), _model(model) {}
	
	virtual bool IsDrawable() const override { return true; }

	virtual recondite::Model* GetModel() { return _model; };
	virtual void SetModel(recondite::Model* model) { _model = model; }

protected:
	recondite::Model* _model;
};