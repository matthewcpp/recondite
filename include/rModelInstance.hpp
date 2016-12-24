#pragma once

#include <vector>
#include <memory>

#include "rBuild.hpp"

#include "asset/rModel.hpp"

namespace recondite {
	class RECONDITE_API ModelInstance {
	public:
		ModelInstance(Model* model);

		inline const Model* GetModel() const;

		rMaterial* GetTriangleMeshInstanceMaterial(size_t index);
		const rMaterial* GetTriangleMeshMaterial(size_t index) const;

		rMaterial* GetLineMeshInstanceMaterial(size_t index);
		const rMaterial* GetLineMeshMaterial(size_t index) const;

	private:
		void Init();

	private:
		Model* _model;

		std::vector<rMaterial*> _triangleMeshInstanceMaterials;
		std::vector<rMaterial*> _lineMeshInstanceMaterials;
		std::vector<std::unique_ptr<rMaterial>> _instanceMaterials;

		rNO_COPY_CLASS(ModelInstance)
	};


	inline const Model* ModelInstance::GetModel() const {
		return _model;
	}
}