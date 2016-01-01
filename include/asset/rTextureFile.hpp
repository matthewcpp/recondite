#ifndef R_TEXTUREFILE_HPP
#define R_TEXTUREFILE_HPP

#include <memory>
#include <cstdint>

#include "rDefs.hpp"
#include "rBuild.hpp"
#include "rTextureData.hpp"
#include "rFileSystem.hpp"

#include "stream/rIStream.hpp"
#include "stream/rOStream.hpp"

class RECONDITE_API rTextureFile{
public:
	rContentError Read(rFileSystem* fileSystem, const rString& path, rTextureData& textureData);
	rContentError Write(rFileSystem* fileSystem, const rString& path, const rTextureData& textureData);

private:


};

#endif