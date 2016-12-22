#include "rStaticMeshBoundingVolume.hpp"

#include "rIntersection.hpp"


bool rStaticMeshBoundingVolume::IntersectsRay(const rRay3& ray, rPickResult& pickResult) const {
	rAlignedBox3 box = _model->GetBoundingBox();
	rVector3 position;
	float closestPickDistance = FLT_MAX;

	if (rIntersection::RayIntersectsAlignedBox(ray, box, &position)) {
		for (size_t i = 0; i < _model->GetTriangleMeshCount(); i++) {
			recondite::Mesh* mesh = _model->GetTriangleMesh(i);
			box = mesh->GetBoundingBox();

			if (rIntersection::RayIntersectsAlignedBox(ray, box, &position)) {
				float pickDistance = position.Distance(ray.origin);

				if (pickResult.hit && closestPickDistance < pickDistance) {
					continue;
				}
				else {
					pickResult.model = _model;
					pickResult.mesh = mesh;
					pickResult.point = position;
					pickResult.hit = true;
				}
			}
		}
	}

	return false;
}

void rStaticMeshBoundingVolume::SetModel(recondite::Model* model) {
	_model = model;
}

rAlignedBox3 rStaticMeshBoundingVolume::FitBox() const {
	return _model->GetBoundingBox();
}

