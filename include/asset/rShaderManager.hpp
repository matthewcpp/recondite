#ifndef R_SHADERMANAGER_HPP
#define R_SHADERMANAGER_HPP

#include "rBuild.hpp"
#include "rGraphicsDevice.hpp"
#include "rFileSystem.hpp"

#include "rShader.hpp"

class RECONDITE_API rShaderManager {
public:
	rShaderManager(rGraphicsDevice* graphicsDevice, rFileSystem* fileSystem);
	~rShaderManager();
public:

	rShader* LoadFromPath(const rString& directory, const rString& name);
	rShader* Load(const rString& vertex, const rString& fragment, const rString& name);

	rShader* Get(const rString& name);
	int Delete(const rString& name);

	void Clear();

	rShader* DefaultModelShader();
	rShader* DefaultLineShader();
	rShader* DefaultPrimitiveShader();
	rShader* DefaultSpriteShader();
	rShader* DefaultTextShader();

private:
	struct Impl;
	Impl* _impl;
};

#endif