#ifndef R_SHADERMANAGER_HPP
#define R_SHADERMANAGER_HPP

#include <map>
#include <memory>
#include <functional>

#include "rBuild.hpp"
#include "rGraphicsDevice.hpp"
#include "rFileSystem.hpp"

#include "rAssetManager.hpp"

#include "rShader.hpp"
#include "rShaderData.hpp"
#include "rShaderFile.hpp"

class rShaderManager : public rAssetManager<rShader, rShaderData, rShaderFile>{
public:
	rShaderManager(rGraphicsDevice* graphicsDevice, rFileSystem* fileSystem);

public:

	rShader* DefaultModelShader();
	rShader* DefaultLineShader();
	rShader* DefaultPrimitiveShader();

	virtual rShader* CreateAssetFromData(const rShaderData& shaderData, const rString& name) override;
	virtual void DisposeAsset(rShader* shader) override;

private:
	rGraphicsDevice* m_graphicsDevice;
};

#endif