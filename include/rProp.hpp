#ifndef R_PROP_HPP
#define R_PROP_HPP

#include "rBuild.hpp"
#include "rActor3.hpp"

#include "asset/rModel.hpp"

class RECONDITE_API rProp : public rActor3{
public:
	rProp(rModel* model, const rString& id, rEngine* engine);

	virtual rString ClassName() const override;

	virtual void Draw() override;

	rModel* Model();
	void SetModel(rModel* model);

protected:
	virtual void DoRecalculateBoundingVolume() override;
	virtual riBoundingVolume* DoGetBoundingVolume() override;

private:
	rModel* m_model;
	rAlignedBoxBoundingVolume m_boundingVolume;
};

#endif