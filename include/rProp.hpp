#ifndef R_PROP_HPP
#define R_PROP_HPP

#include "rBuild.hpp"
#include "rDrawable.hpp"

#include "asset/rModel.hpp"

class RECONDITE_API rProp : public rDrawable {
public:
	rProp(recondite::Model* model, const rString& id, rEngine* engine);
	rProp(const rString& id, rEngine* engine);

public:
	virtual rString ClassName() const override;
	virtual void SetModel(recondite::Model* model) override;

	virtual void Draw() override;

	virtual bool DoSerialize(riSerializationTarget* target, rSerializeAction action);

public:
	virtual size_t GetNumAssets() const override;
	virtual bool GetAsset(size_t index, rAssetType& assetType, rString& name) const override;

private:
	rNO_COPY_CLASS(rProp)
};

#endif