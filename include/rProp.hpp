#ifndef R_PROP_HPP
#define R_PROP_HPP

#include "rBuild.hpp"
#include "rActor3.hpp"

#include "asset/rModel.hpp"

class RECONDITE_API rProp : public rActor3{
public:
	rProp(recondite::Model* model, const rString& id, rEngine* engine);

	virtual rString ClassName() const override;

	virtual void Draw() override;

	recondite::Model* Model();
	void SetModel(recondite::Model* model);

protected:
	virtual void DoRecalculateBoundingVolume() override;
	virtual riBoundingVolume* DoGetBoundingVolume() override;

private:
	recondite::Model* m_model;
	rAlignedBoxBoundingVolume m_boundingVolume;
};

#endif