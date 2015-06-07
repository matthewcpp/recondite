#ifndef R_TEXTUREFILE_HPP
#define R_TEXTUREFILE_HPP

#include <memory>

#include "rDefs.hpp"
#include "rBuild.hpp"
#include "rTextureData.hpp"
#include "rFileSystem.hpp"

#include "stream/rIStream.hpp"
#include "stream/rOStream.hpp"

class RECONDITE_API rTextureFile{
	static rContentError Read(rFileSystem* fileSystem, const rString& path, std::unique_ptr<rTextureData>& textureData);
};

#endif