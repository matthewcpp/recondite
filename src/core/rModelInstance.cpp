#include "rModelInstance.hpp"

namespace recondite {
	ModelInstance::ModelInstance(Model* model) {
		_model = model;

		Init();
	}

	void ModelInstance::Init() {
		size_t traingleMeshCount = _model->GetTriangleMeshCount();
		size_t lineMeshCount = _model->GetLineMeshCount();

		if (traingleMeshCount > 0) {
			_triangleMeshInstanceMaterials.resize(traingleMeshCount);

			for (size_t i = 0; i < traingleMeshCount; i++) {
				_triangleMeshInstanceMaterials[i] = _model->GetTriangleMesh(i)->GetMaterial();
			}
		}

		if (lineMeshCount > 0) {
			_lineMeshInstanceMaterials.resize(lineMeshCount);

			for (size_t i = 0; i < lineMeshCount; i++) {
				_lineMeshInstanceMaterials[i] = _model->GetLineMesh(i)->GetMaterial();
			}
		}
	}

	rMaterial* ModelInstance::GetTriangleMeshInstanceMaterial(size_t index) {
		if (_triangleMeshInstanceMaterials[index] == _model->GetTriangleMesh(index)->GetMaterial()) {
			rMaterial* instanceMaterial = new rMaterial();
			instanceMaterial->Copy(*_triangleMeshInstanceMaterials[index]);

			_triangleMeshInstanceMaterials[index] = instanceMaterial;
			_instanceMaterials.emplace_back(instanceMaterial);

			return instanceMaterial;
		}
		else {
			return _triangleMeshInstanceMaterials[index];
		}
	}

	const rMaterial* ModelInstance::GetTriangleMeshMaterial(size_t index) const {
		return _triangleMeshInstanceMaterials[index];
	}

	rMaterial* ModelInstance::GetLineMeshInstanceMaterial(size_t index) {
		if (_lineMeshInstanceMaterials[index] == _model->GetLineMesh(index)->GetMaterial()) {
			rMaterial* instanceMaterial = new rMaterial();
			instanceMaterial->Copy(*_lineMeshInstanceMaterials[index]);

			_lineMeshInstanceMaterials[index] = instanceMaterial;
			_instanceMaterials.emplace_back(instanceMaterial);

			return instanceMaterial;
		}
		else {
			return _lineMeshInstanceMaterials[index];
		}
	}

	const rMaterial* ModelInstance::GetLineMeshMaterial(size_t index) const {
		return _lineMeshInstanceMaterials[index];
	}
}

