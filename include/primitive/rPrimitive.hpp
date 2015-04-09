#ifndef R_PRIMITIVE_HPP
#define R_PRIMITIVE_HPP

#include "rBuild.hpp"
#include "rActor3.hpp"

#include "data/rModelGeometryData.hpp"

class RECONDITE_API rPrimitive : public rActor3{
public:
	rPrimitive(const rString& id, rEngine* engine);
	~rPrimitive();

	void SetColor(const rColor& color);
	void SetEdgeColor(const rColor& color);
	void SetFaceColor(const rColor& color);

	rColor EdgeColor() const;
	rColor FaceColor() const;

	virtual void Draw();

	virtual void OnDelete() override;

protected:
	virtual bool DoSerialize(riSerializationTarget* target);
	virtual void OnLoad();

	virtual void CreateGeometry(rModelGeometryData& geometry) = 0;
	void InvalidateGeometry();

private:
	void RecreateGeometry();

private:
	rColor m_edgeColor;
	rColor m_faceColor;
	bool m_geometryInvalid;

	rGeometry* m_geometry;
};

#endif