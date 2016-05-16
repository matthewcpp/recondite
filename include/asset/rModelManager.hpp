#ifndef R_MODELMANAGER_HPP
#define R_MODELMANAGER_HPP

#include "rBuild.hpp"
#include "rFileSystem.hpp"

#include "rAssetManager.hpp"

#include "rGeometryManager.hpp"
#include "rShaderManager.hpp"

#include "rModel.hpp"
#include "rModelData.hpp"
#include "rModelFile.hpp"

class RECONDITE_API rModelManager : public rAssetManager < rModel, rModelData, rModelFile > {
public:
	rModelManager(rFileSystem* fileSysytem, rShaderManager* shaderManager, rGeometryManager* geometryManager);

protected:
	virtual rModel* CreateAssetFromData(const rModelData& modelData, const rString& name) override;
	virtual void DisposeAsset(rModel* model) override;

private:
	rGeometryManager* m_geometryManager;
	rShaderManager* m_shadermanager;
};

#endif