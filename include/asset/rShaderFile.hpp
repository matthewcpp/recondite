#ifndef R_SHADERFILE_HPP
#define R_SHADERFILE_HPP

#include <memory>

#include "rDefs.hpp"
#include "rBuild.hpp"

#include "rShaderData.hpp"
#include "rFileSystem.hpp"

#include "stream/rIStream.hpp"
#include "stream/rOStream.hpp"

class RECONDITE_API rShaderFile{
	static rContentError Read(rFileSystem* fileSystem, const rString& path, std::unique_ptr<rShaderData>& shaderData);
};


#endif