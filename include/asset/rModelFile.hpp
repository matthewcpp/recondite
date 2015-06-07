#ifndef R_MODELFILE_HPP
#define R_MODELFILE_HPP

#include <memory>

#include "rBuild.hpp"
#include "rDefs.hpp"
#include "rFileSystem.hpp"
#include "rModelData.hpp"

class RECONDITE_API rModelFile{
public:
	static rContentError Read(rFileSystem* fileSystem, const rString& path, std::unique_ptr<rModelData>& modelData);
};

#endif