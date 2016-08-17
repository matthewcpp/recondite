#ifndef R_MODELMANAGER_HPP
#define R_MODELMANAGER_HPP

#include "rBuild.hpp"
#include "rFileSystem.hpp"

#include "rAssetManager.hpp"

#include "rShaderManager.hpp"

#include "rModel.hpp"
#include "rModelData.hpp"

using namespace recondite;

class RECONDITE_API rModelManager{
public:
	rModelManager(rFileSystem* fileSysytem, rGraphicsDevice* graphicsDevice);
	~rModelManager();

	void Clear();
	Model* LoadFromData(const ModelData& modelData, const rString& name);
	bool Delete(const rString& name);

private:
	struct Impl;
	Impl* _impl;
};

#endif