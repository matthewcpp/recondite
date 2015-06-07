#ifndef R_FILESYSTEM_HPP
#define R_FILESYSTEM_HPP

#include <memory>

#include "rBuild.hpp"
#include "rString.hpp"

#include "stream/rIFileStream.hpp"
#include "stream/rOFileStream.hpp"

class rFileSystem{

public:
	typedef std::shared_ptr<rIStream> rIStreamRef;
	typedef std::shared_ptr<rOStream> rOStreamRef;

	rIStreamRef GetReadFileRef(const rString& path);
	rOStreamRef GetWriteFileRef(const rString& path);
};

#endif