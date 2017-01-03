#pragma once

#include <vector>
#include <cstdint>

#include "rBuild.hpp"

#include "interface/riBoundingVolume.hpp"
#include "asset/rModel.hpp"

class RECONDITE_API rStaticMeshBoundingVolume : public riBoundingVolume {
public:
	rStaticMeshBoundingVolume(recondite::Model* model);
	virtual bool IntersectsRay(const rRay3& ray, rPickResult& pickResult) const;
	virtual rAlignedBox3 FitBox() const;

	void SetModel(recondite::Model* model);

private:
	void _CheckMesh(recondite::Mesh* mesh, const rRay3& ray, rPickResult& pickResult) const;

private:
	recondite::Model* _model;
};