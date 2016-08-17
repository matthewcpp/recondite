#ifndef R_PRIMITIVEGRID_HPP
#define R_PRIMITIVEGRID_HPP

#include "rBuild.hpp"

#include "primitive/rPrimitive.hpp"
#include "primitive/rPrimitiveGeometry.hpp"

class RECONDITE_API rPrimitiveGrid : public rPrimitive {
public:
	rPrimitiveGrid(const rString& id, rEngine* engine);

public:
	virtual rString ClassName() const;

	float Width() const;
	void SetWidth(float width);

	float Depth() const;
	void SetDepth(float depth);

	int Rows() const;
	void SetRows(int rows);

	int Colums() const;
	void SetColumns( int columns);

protected:
	virtual bool DoSerialize(riSerializationTarget* target) override;
	virtual void CreateGeometry(ModelData& modelData) override;
	virtual void DoRecalculateBoundingVolume() override;
	virtual riBoundingVolume* DoGetBoundingVolume()override;


private:
	rAlignedBoxBoundingVolume m_boundingVolume;

	float m_width;
	float m_depth;

	int m_rows;
	int m_columns;
};

#endif