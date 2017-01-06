#ifndef R_PRIMITIVE_HPP
#define R_PRIMITIVE_HPP

#include "rBuild.hpp"
#include "rDrawable.hpp"

#include "asset/rModelData.hpp"
#include "rModelInstance.hpp"

using namespace recondite;

class RECONDITE_API rPrimitive : public rDrawable {
public:
	rPrimitive(const rString& id, rEngine* engine);

	void SetColor(const rColor& color);
	void SetEdgeColor(const rColor& color);
	void SetFaceColor(const rColor& color);

	rColor EdgeColor() const;
	rColor FaceColor() const;

	void RecreateGeometry();

	virtual recondite::ModelInstance* GetModelInstance() override;
	virtual void Draw();

	virtual void OnDelete() override;

public:
	virtual size_t GetNumAssets() const override;
	virtual bool GetAsset(size_t index, rAssetType& assetType, rString& name) const override;

protected:
	virtual bool DoSerialize(riSerializationTarget* target, rSerializeAction action);
	virtual void OnLoad();

	virtual void CreateGeometry(ModelData& modelData) = 0;
	virtual void RecalculateBoundingVolume() = 0;
	void InvalidateGeometry();

	void UpdateMaterials();

private:
	rColor m_edgeColor;
	rColor m_faceColor;
	bool m_geometryInvalid;
};

#endif