#pragma once

#include <vector>
#include <cstdint>

#include "rBuild.hpp"

#include "interface/riBoundingVolume.hpp"
#include "asset/rModel.hpp"

class RECONDITE_API rStaticMeshBoundingVolume : public riBoundingVolume {
public:
	virtual bool IntersectsRay(const rRay3& ray, rPickResult& pickResult) const;
	virtual rAlignedBox3 FitBox() const;

	void SetModel(recondite::Model* model);
private:
	recondite::Model* _model;
};