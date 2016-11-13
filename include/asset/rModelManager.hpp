#ifndef R_MODELMANAGER_HPP
#define R_MODELMANAGER_HPP

#include "rBuild.hpp"
#include "rFileSystem.hpp"

#include "rModel.hpp"
#include "rModelData.hpp"

#include "rGraphicsDevice.hpp"
#include "rTextureManager.hpp"

using namespace recondite;

class RECONDITE_API rModelManager{
public:
	rModelManager(rFileSystem* fileSysytem, rGraphicsDevice* graphicsDevice, rTextureManager* textureManager);
	~rModelManager();

	void Clear();
	Model* LoadFromData(ModelData& modelData, const rString& name);
	bool Delete(const rString& name);
	Model* Get(const rString& name);

private:
	struct Impl;
	Impl* _impl;
};

#endif