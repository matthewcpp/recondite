#include "rStaticMeshBoundingVolume.hpp"

#include "rIntersection.hpp"


bool rStaticMeshBoundingVolume::IntersectsRay(const rRay3& ray, rPickResult& pickResult) const {
	rAlignedBox3 box = _model->GetBoundingBox();

	if (rIntersection::RayIntersectsAlignedBox(ray, box)) {
		for (size_t i = 0; i < _model->GetLineMeshCount(); i++) {
			rPickResult current;
			_CheckMesh(_model->GetLineMesh(i), ray, current);

			if (current.hit && current.distanceSquared < pickResult.distanceSquared) {
				pickResult = current;
			}
		}

		for (size_t i = 0; i < _model->GetTriangleMeshCount(); i++) {
			rPickResult current;
			_CheckMesh(_model->GetTriangleMesh(i), ray, current);

			if (current.hit && current.distanceSquared < pickResult.distanceSquared) {
				pickResult = current;
			}
		}
	}

	return pickResult.hit;
}

void rStaticMeshBoundingVolume::_CheckMesh(recondite::Mesh* mesh, const rRay3& ray, rPickResult& pickResult) const{
	rAlignedBox3 box = mesh->GetBoundingBox();

	if (rIntersection::RayIntersectsAlignedBox(ray, box, &pickResult.point)) {
		pickResult.distanceSquared = pickResult.point.DistanceSquared(ray.origin);
		pickResult.model = _model;
		pickResult.mesh = mesh;
		pickResult.hit = true;
	}
}

rStaticMeshBoundingVolume::rStaticMeshBoundingVolume(recondite::Model* model) {
	SetModel(model);
}

void rStaticMeshBoundingVolume::SetModel(recondite::Model* model) {
	_model = model;
}

rAlignedBox3 rStaticMeshBoundingVolume::FitBox() const {
	return _model->GetBoundingBox();
}

