#ifndef R_MATERIALFILE_HPP
#define R_MATERIALFILE_HPP

#include <memory>

#include "rBuild.hpp"
#include "rDefs.hpp"

#include "rMaterialData.hpp"
#include "rFileSystem.hpp"

class RECONDITE_API rMaterialFile {
public:
	static rContentError Read(rFileSystem* fileSystem, const rString& path, std::unique_ptr<rMaterialData>& materialData);
};

#endif