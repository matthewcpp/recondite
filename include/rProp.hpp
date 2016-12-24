#ifndef R_PROP_HPP
#define R_PROP_HPP

#include "rBuild.hpp"
#include "rDrawable.hpp"

#include "asset/rModel.hpp"

class RECONDITE_API rProp : public rDrawable {
public:
	rProp(recondite::Model* model, const rString& id, rEngine* engine);

	virtual rString ClassName() const override;

	virtual void Draw() override;

protected:
	virtual void DoRecalculateBoundingVolume() override;
	virtual riBoundingVolume* DoGetBoundingVolume() override;

private:
	rAlignedBoxBoundingVolume m_boundingVolume;

	rNO_COPY_CLASS(rProp)
};

#endif