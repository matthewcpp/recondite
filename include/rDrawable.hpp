#pragma once

#include <memory>

#include "rBuild.hpp"

#include "rString.hpp"
#include "rEngine.hpp"

#include "rActor3.hpp"
#include "rModelInstance.hpp"

class RECONDITE_API rDrawable : public rActor3 {
public:
	rDrawable(const rString& id, rEngine* engine) : rActor3(id, engine), _modelInstance(nullptr) {}
	rDrawable(recondite::ModelInstance* model, const rString& id, rEngine* engine) : rActor3(id, engine), _modelInstance(model) {}
	
	virtual bool IsDrawable() const override { return true; }

	virtual recondite::ModelInstance* GetModelInstance() { 
		return _modelInstance.get(); 
	}

	virtual void SetModel(recondite::Model* model) { 
		if (model) {
			_modelInstance.reset(new recondite::ModelInstance(model));
		}
		else {
			_modelInstance.reset(nullptr);
		}
	}

protected:
	std::unique_ptr<recondite::ModelInstance> _modelInstance;

	rNO_COPY_CLASS(rDrawable)
};