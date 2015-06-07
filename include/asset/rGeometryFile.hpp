#ifndef R_GEOMETRYDATAFILE_HPP
#define R_GEOMETRYDATAFILE_HPP

#include "rBuild.hpp"
#include "rDefs.hpp"
#include "rString.hpp"
#include "rFileSystem.hpp"

#include "rGeometryData.hpp"


#define rGEOMETRY_MAGIC_NUMBER 1868916594 //rgeo

class RECONDITE_API rGeometryFile{
public:
	static rContentError Read(rFileSystem* fileSystem, const rString& path, std::unique_ptr<rGeometryData>& geometryData);
};

#endif