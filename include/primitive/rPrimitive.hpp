#ifndef R_PRIMITIVE_HPP
#define R_PRIMITIVE_HPP

#include "rBuild.hpp"
#include "rActor3.hpp"

#include "data/rTexCoordGeometryData.hpp"
#include "data/rModelData.hpp"
#include "rModel.hpp"

class RECONDITE_API rPrimitive : public rActor3{
public:
	rPrimitive(const rString& id, rEngine* engine);

	void SetColor(const rColor& color);
	void SetEdgeColor(const rColor& color);
	void SetFaceColor(const rColor& color);

	rColor EdgeColor() const;
	rColor FaceColor() const;

	rModel* Model() const;
	void RecreateGeometry();

	virtual void Draw();

	virtual void OnDelete() override;

protected:
	virtual bool DoSerialize(riSerializationTarget* target);
	virtual void OnLoad();

	virtual void CreateGeometry(rGeometryData& geometry) = 0;
	void InvalidateGeometry();

	void UpdateMaterials();

private:
	rColor m_edgeColor;
	rColor m_faceColor;
	bool m_geometryInvalid;

	rModel* m_model;
};

#endif