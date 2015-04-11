#ifndef R_PROP_HPP
#define R_PROP_HPP

#include "rBuild.hpp"
#include "rActor3.hpp"

#include "rModel.hpp"

class RECONDITE_API rProp : public rActor3{
public:
	rProp(rModel* model, const rString& id, rEngine* engine);

	virtual rString ClassName() const override;

	virtual void Draw() override;

	rModel* Model();
	void SetModel(rModel* model);
private:
	rModel* m_model;
};

#endif