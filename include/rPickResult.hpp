#pragma once

#include <cstdint>

#include "rBuild.hpp"
#include "rVector3.hpp"

#include "asset/rModel.hpp"

class rActor3;

struct RECONDITE_API rPickResult {
	bool hit;
	rActor3* actor;
	recondite::Model* model;
	recondite::Mesh* mesh;
	rVector3 point;
	uint32_t triangleId;
	float distanceSquared;

	rPickResult() : hit(false), actor(nullptr), model(nullptr), mesh(nullptr), point(rVector3::ZeroVector), triangleId(UINT32_MAX), distanceSquared(FLT_MAX) {}
};